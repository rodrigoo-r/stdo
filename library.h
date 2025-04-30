/*
* This code is distributed under the terms of the GNU General Public License.
 * For more information, please refer to the LICENSE file in the root directory.
 * -------------------------------------------------
 * Copyright (C) 2025 Rodrigo R.
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it
 * under certain conditions; type `show c' for details.
*/

#ifndef STDO_LIBRARY_H
#define STDO_LIBRARY_H

/**
 * @brief Flushes the write buffer by writing its contents to standard output.
 *
 * This function uses a system call to write the contents of the global buffer
 * `stdo_write_buffer` to the standard output (file descriptor 1). After writing,
 * it resets the buffer index to 0, effectively clearing the buffer.
 */
void flush_write_buffer();

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
void print(const char* str);

/**
 * @brief Writes a string followed by a newline to the global write buffer.
 *
 * This function first writes the given string to the global write buffer
 * using the `print` function, and then appends a newline character (`\n`)
 * to the buffer. If the buffer becomes full, it is flushed to standard output.
 *
 * @param str The string to write to the buffer. If `str` is NULL, the function does nothing.
 */
void println(const char* str);

#endif //STDO_LIBRARY_H