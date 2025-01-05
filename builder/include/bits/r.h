
#ifndef R_H
#define R_H

#include <stdint.h>
#include <stddef.h>

/**
 * Argument Types
 * - Defines the types of arguments that can be described in ArgDesc.
 */
#define ARGTYPE_SCALAR    0
#define ARGTYPE_PTR_IN    1
#define ARGTYPE_PTR_OUT   2
#define ARGTYPE_PTR_INOUT 3

/**
 * ArgDesc Structure
 * - Used to describe individual arguments for marshalling.
 */
typedef struct {
    int32_t arg_type;     // Type of the argument (e.g., ARGTYPE_SCALAR, PTR_IN, etc.).
    int32_t size_bytes;   // Size of the argument in bytes.
    void*   data_ptr;     // Pointer to the argument's data.
} ArgDesc;

/**
 * Host Function Declaration
 * - Function to send a request buffer and receive a response buffer.
 * - Implemented externally.
 *
 * Parameters:
 *   - buffer: Pointer to the request buffer.
 *   - length: Length of the request buffer.
 *   - out_response_len: Pointer to receive the length of the response buffer.
 *
 * Returns:
 *   - Pointer to the newly allocated response buffer, or NULL on error.
 */

__attribute__((import_module("env"), import_name("r")))

extern uint8_t* r(const uint8_t* buffer, size_t length, size_t* out_response_len);

/**
 * create_request_buffer
 * - Constructs a request buffer from an array of ArgDesc instances.
 *
 * Parameters:
 *   - num_args: Number of arguments in the array.
 *   - args: Array of ArgDesc instances.
 *   - out_len: Pointer to receive the size of the request buffer.
 *
 * Returns:
 *   - Pointer to the newly allocated request buffer, or NULL on error.
 */
uint8_t* create_request_buffer(int num_args, const ArgDesc* args, size_t* out_len);

/**
 * parse_and_patch_response
 * - Parses the response buffer and applies patches to pointer arguments.
 *
 * Parameters:
 *   - resp: Pointer to the response buffer.
 *   - resp_len: Length of the response buffer.
 *   - num_args: Number of arguments in the original ArgDesc array.
 *   - args: Array of ArgDesc instances to be patched.
 *
 * Returns:
 *   - The syscall return value (int32_t).
 */
int32_t parse_and_patch_response(const uint8_t* resp, size_t resp_len,
                                 int num_args, ArgDesc* args);

/**
 * create_and_send_buffer_ext
 * - High-level wrapper that builds the request buffer, invokes the host
 *   function, and processes the response.
 *
 * Parameters:
 *   - num_args: Number of arguments in the array.
 *   - args: Array of ArgDesc instances.
 *
 * Returns:
 *   - The syscall return value (int32_t).
 */
int32_t create_and_send_buffer_ext(int num_args, ArgDesc* args);

#endif // R_H

