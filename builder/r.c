#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

// Declaration of the host function that returns a pointer to another buffer
extern uint8_t* r(const uint8_t* buffer);

int32_t create_and_send_buffer(int num_args, ...) {
    // Calculate the total buffer size needed
    size_t buffer_size = (sizeof(int32_t) + 1) * num_args;  // 4 bytes per int + 1 byte for null terminator

    // Allocate memory for the buffer
    uint8_t* buffer = (uint8_t*)malloc(buffer_size);
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        return -1; // Return an error code
    }

    // Initialize variadic argument list
    va_list args;
    va_start(args, num_args);

    // Fill the buffer with the integers and null terminators
    uint8_t* current_position = buffer;
    for (int i = 0; i < num_args; i++) {
        int32_t arg = va_arg(args, int32_t);
        *(int32_t*)current_position = arg;
        current_position += sizeof(int32_t);
        *current_position = 0x00; // Null terminator
        current_position += 1;
    }

    // Clean up the argument list
    va_end(args);

    // Call the host function with the buffer
    uint8_t* returned_buffer = r(buffer);

    // Free the original buffer since it's no longer needed
    free(buffer);

    // Extract the first integer from the returned buffer
    int32_t returned_value = *(int32_t*)returned_buffer;

    // Check if there are additional values in the returned buffer
    uint8_t* next_position = returned_buffer + sizeof(int32_t) + 1;
    if (*next_position != 0x00) { // If there's more data after the first value
        printf("These are values that must replace referenced values from arguments:\n");
        while (*next_position != 0x00) {
            int32_t additional_value = *(int32_t*)next_position;
            printf("%d\n", additional_value);
            next_position += sizeof(int32_t) + 1; // Move to the next value
        }
    }

    // Optionally free the returned buffer if it's managed by the host environment
    // For now, assume the host handles the returned buffer's memory management

    return returned_value;
}
