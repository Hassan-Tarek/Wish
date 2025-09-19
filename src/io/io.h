#define _GNU_SOURCE

#ifndef IO_H
#define IO_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "../error/error.h"

#define INITIAL_CAPACITY 256

/**
 * @brief Prints the shell prompt to standard output.
 */
void print_prompt(void);

/**
 * @brief Prints a formatted message to a specified output stream.
 *
 * Uses a `printf`-style format string with variable arguments.
 *
 * @param out The output stream (e.g., stdout or stderr).
 * @param format The format string (printf-style).
 * @param ... Variable arguments for formatting.
 */
void print_message(FILE *out, const char *format, ...);

/**
 * @brief Reads a single command line from standard input.
 *
 * Dynamically allocates memory for the line read from stdin.
 *
 * @return A pointer to the command string, or NULL if EOF or error occurs.
 */
char* read_command(void);

/**
 * @brief Reads multiple commands from a file.
 *
 * Opens the given file, reads all lines, and stores each command
 * as a string in a dynamically allocated array.
 *
 * @param filename The name of the file containing commands.
 *
 * @return A NULL-terminated array of command strings, or NULL if
 *         the file could not be read. Caller must free the array
 *         and each string.
 */
char** read_commands_from_file(const char* filename);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IO_H */
