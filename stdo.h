/*
* This code is distributed under the terms of the GNU General Public License.
 * For more information, please refer to the LICENSE file in the root directory.
 * -------------------------------------------------
 * Copyright (C) 2025 Rodrigo R.
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it
 * under certain conditions; type `show c' for details.
*/

#ifndef FLUENT_LIBC_STDO_LIBRARY_H
#define FLUENT_LIBC_STDO_LIBRARY_H

#if defined(__cplusplus)
extern "C"
{
#endif

// Define true/false values
#ifndef FLUENT_LIBC_RELEASE
#   include <std_bool.h> // fluent_libc
#else
#   include <fluent/std_bool/std_bool.h> // fluent_libc
#endif

// Define the size of the buffer for buffered output
#ifndef STDO_WRITE_BUFFER_SIZE
#   define STDO_WRITE_BUFFER_SIZE 1024
#endif

// Define a global buffer
char stdo_write_buffer[STDO_WRITE_BUFFER_SIZE];
int stdo_write_buffer_index = 0;
// Keep track of whether we have added an atexit listener
int stdo_has_atexit_listener = FALSE;

#ifndef _WIN32 // Guard against Windows incompatibility
#   include <stdlib.h>
#   include <syscall.h>
#   include <unistd.h>
#else
#   include <stdio.h> // Default to use stdio.h for Windows
#endif

/**
 * @brief Flushes the write buffer by writing its contents to standard output.
 *
 * This function uses a system call to write the contents of the global buffer
 * `stdo_write_buffer` to the standard output (file descriptor 1). After writing,
 * it resets the buffer index to 0, effectively clearing the buffer.
 */
static inline void flush_write_buffer()
{
#ifndef _WIN32 // Guard against Windows incompatibility
    // Make a syscall to write the buffer
    syscall(SYS_write, 1, stdo_write_buffer, stdo_write_buffer_index);
    // Reset the index
    stdo_write_buffer_index = 0;
#else
    fflush(stdout); // For Windows, flush the standard output
#endif
}

/**
 * @brief Writes a string to the global write buffer.
 *
 * This function adds the given string to the global write buffer, flushing the buffer
 * to standard output if it becomes full. If the buffer is not already set to flush
 * on program exit, it registers an `atexit` listener to ensure the buffer is flushed
 * when the program terminates.
 *
 * @param str The string to write to the buffer. If `str` is NULL, the function does nothing.
 */
static inline void print(const char* str)
{
#ifndef _WIN32 // Guard against Windows incompatibility
    // Check if we have exit listeners
    if (!stdo_has_atexit_listener)
    {
        // Add an exit listener
        atexit(flush_write_buffer);
    }

    // Drop NULL strings
    if (str == NULL)
    {
        return;
    }

    // Add character by character to the buffer
    while (*str != '\0')
    {
        // Get the character
        const char c = *str;

        // Check if the buffer has enough space
        if (stdo_write_buffer_index == STDO_WRITE_BUFFER_SIZE)
        {
            flush_write_buffer();
        }

        // Write the character to the buffer
        stdo_write_buffer[stdo_write_buffer_index] = c;
        stdo_write_buffer_index++;

        // Move to the next character
        str++;
    }
#else
    // For Windows, use standard output directly
    if (str != NULL)
    {
        printf("%s", str);
    }
#endif
}

/**
 * @brief Writes a string followed by a newline to the global write buffer.
 *
 * This function first writes the given string to the global write buffer
 * using the `print` function, and then appends a newline character (`\n`)
 * to the buffer. If the buffer becomes full, it is flushed to standard output.
 *
 * @param str The string to write to the buffer. If `str` is NULL, the function does nothing.
 */
static inline void println(const char* str)
{
#ifndef _WIN32 // Guard against Windows incompatibility
    print(str);
    print("\n");
#else
    // For Windows, use standard output directly
    if (str != NULL)
    {
        puts(str);
    }
#endif
}

#if defined(__cplusplus)
}
#endif

#endif //FLUENT_LIBC_STDO_LIBRARY_H