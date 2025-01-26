/*this file really lives in src/network/ for the compiler, remove ?*/

/**
 * r.c
 *
 * This file contains:
 *   - A structure for describing arguments (scalar or pointer).
 *   - create_and_send_buffer_ext(...) that builds the request buffer
 *     and calls r(...).
 *   - Example usage: gettimeofday(...) using the new approach.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>

// We'll define these "type" codes for arguments:
#define ARGTYPE_SCALAR    0
#define ARGTYPE_PTR_IN    1
#define ARGTYPE_PTR_OUT   2
#define ARGTYPE_PTR_INOUT 3

// Declaration of the host function that proxies the buffer to the server:
//
//   r(request_buffer, request_length, &response_length)
//   -> returns pointer to newly allocated buffer with response data
//      or NULL on error.
//
// You could rename it or expand it as needed.
extern uint8_t* r(const uint8_t* buffer, size_t length, size_t* out_response_len);

/**
 *  A small struct that we can pass around describing each argument.
 *  In real usage, you might generate this automatically from a higher-level
 *  function signature parser, or just manually for each function.
 */
typedef struct {
    int32_t arg_type;     // ARGTYPE_SCALAR, PTR_IN, PTR_OUT, ...
    int32_t size_bytes;   // For scalar, typically 4. For pointer, the struct or buffer size.
    void*   data_ptr;     // The actual data. If SCALAR, points to a 4-byte int. If PTR_IN, the user data. If PTR_OUT, might be a placeholder, etc.
} ArgDesc;

/**
 * create_request_buffer:
 *    Given an array of ArgDesc, build the final buffer to send:
 *      [num_args: int32_t]
 *      repeated for i in 0..(num_args-1):
 *        [arg_type: int32_t]
 *        [size_bytes: int32_t]
 *        [raw_data: size_bytes]  (if type != PTR_OUT, or if we want to send data for inout)
 *
 *    Returns a newly allocated buffer + length in *out_len.
 */
static uint8_t* create_request_buffer(int num_args, const ArgDesc* args, size_t* out_len)
{
    // Calculate total size
    //   4 bytes for num_args
    // For each argument: 4 bytes for arg_type + 4 bytes for size_bytes + size_bytes for data (sometimes 0)
    size_t total = sizeof(int32_t);
    for (int i = 0; i < num_args; i++) {
        total += sizeof(int32_t) + sizeof(int32_t); // arg_type + size_bytes
        // If pointer is OUT only, we typically do not send data (size might be 0 or the real size).
        // If it's IN or INOUT, we send the data. For SCALAR, we always send 4 bytes.
        // We'll always reserve size_bytes space, but for OUT we might fill with zeros.
        total += args[i].size_bytes;
    }

    uint8_t* buffer = (uint8_t*)malloc(total);
    if (!buffer) {
        perror("create_request_buffer: malloc failed");
        *out_len = 0;
        return NULL;
    }

    // Fill it
    size_t offset = 0;

    // Write num_args
    memcpy(buffer + offset, &num_args, sizeof(int32_t));
    offset += sizeof(int32_t);

    for (int i = 0; i < num_args; i++) {
        // write arg_type
        memcpy(buffer + offset, &args[i].arg_type, sizeof(int32_t));
        offset += sizeof(int32_t);

        // write size_bytes
        memcpy(buffer + offset, &args[i].size_bytes, sizeof(int32_t));
        offset += sizeof(int32_t);

        // write data if needed
        if (args[i].size_bytes > 0) {
            // If it's PTR_IN or PTR_INOUT or SCALAR, we have data to send
            // If it's PTR_OUT, we might send zeros or skip.
            // For simplicity, we always write exactly size_bytes (the user can decide).
            if (args[i].arg_type == ARGTYPE_PTR_OUT) {
                // The "client" has no actual data to send. Fill with 0 for clarity.
                memset(buffer + offset, 0, args[i].size_bytes);
            } else {
                // SCALAR, PTR_IN, PTR_INOUT
                memcpy(buffer + offset, args[i].data_ptr, args[i].size_bytes);
            }
            offset += args[i].size_bytes;
        }
    }

    *out_len = total;
    return buffer;
}

/**
 * parse_and_patch_response:
 *    The server's response format is:
 *        [syscall_return_value: int32_t]
 *        [num_patches: int32_t]
 *        For each patch:
 *          [arg_index: int32_t]
 *          [patch_size: int32_t]
 *          [patch_data: patch_size bytes]
 *
 *    We read that, patch the corresponding argument's data_ptr if it is
 *    PTR_OUT or PTR_INOUT, etc.
 *
 *    Returns the syscall_return_value.
 */
static int32_t parse_and_patch_response(const uint8_t* resp, size_t resp_len,
                                        int num_args, ArgDesc* args)
{
    if (resp_len < 8) {
        fprintf(stderr, "parse_and_patch_response: response too short\n");
        return -1;
    }

    int32_t syscall_ret = 0;
    memcpy(&syscall_ret, resp, sizeof(int32_t));
    resp += sizeof(int32_t);
    resp_len -= sizeof(int32_t);

    int32_t num_patches = 0;
    memcpy(&num_patches, resp, sizeof(int32_t));
    resp += sizeof(int32_t);
    resp_len -= sizeof(int32_t);

    for (int i = 0; i < num_patches; i++) {
        if (resp_len < 8) {
            fprintf(stderr, "parse_and_patch_response: truncated patch\n");
            break;
        }
        int32_t arg_index, patch_size;
        memcpy(&arg_index, resp, sizeof(int32_t));
        memcpy(&patch_size, resp + 4, sizeof(int32_t));
        resp += 8;
        resp_len -= 8;

        if (arg_index < 0 || arg_index >= num_args) {
            fprintf(stderr, "parse_and_patch_response: invalid arg_index=%d\n", arg_index);
            // skip or break
            break;
        }
        if ((int32_t)args[arg_index].size_bytes < patch_size) {
            fprintf(stderr, "parse_and_patch_response: server returned bigger patch than our arg size\n");
            // continue or break
        }
        if (resp_len < (size_t)patch_size) {
            fprintf(stderr, "parse_and_patch_response: truncated patch data\n");
            break;
        }

        // Patch the data
        // We assume in real Wasm you do: memcpy(&Module.HEAPU8[ pointer_offset ], resp, patch_size);
        // But here, we'll just do:
        memcpy(args[arg_index].data_ptr, resp, patch_size);

        resp += patch_size;
        resp_len -= patch_size;
    }

    return syscall_ret;
}

/**
 * create_and_send_buffer_ext:
 *   This is the main function your "syscall wrappers" call.
 *   - Takes an array of ArgDesc
 *   - Builds the request buffer
 *   - Calls r()
 *   - Parses the response and patches pointer data
 *   - Returns the syscall's int32_t return value
 */
int32_t create_and_send_buffer_ext(int num_args, ArgDesc* args)
{
    size_t request_len = 0;
    uint8_t* request_buf = create_request_buffer(num_args, args, &request_len);
    if (!request_buf) {
        return -1;
    }

    // Call the host function
    size_t response_len = 0;
    uint8_t* response_buf = r(request_buf, request_len, &response_len);

    free(request_buf);

    if (!response_buf) {
        fprintf(stderr, "create_and_send_buffer_ext: r() returned NULL\n");
        return -1;
    }

    // Parse and patch
    int32_t rv = parse_and_patch_response(response_buf, response_len, num_args, args);

    // If the host does NOT manage free, we free it
    free(response_buf);

    return rv;
}
