#define _GNU_SOURCE

#ifndef ERROR_H
#define ERROR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "../io/io.h"

/**
 * @brief Print an error message to stderr.
 * 
 * Prefixes the message with "wish:" for consistency.
 * 
 * @param error_message The message to display.
 */
void print_error_message(const char *error_message);

/**
 * @brief Print an error message with system error details.
 * 
 * Appends strerror(errno) to the provided message.
 * 
 * @param error_message The message to display.
 */
void print_error_message_errno(const char *error_message);

/**
 * @brief Print a fatal error and terminate the program.
 * 
 * Writes the message to stderr and exits with EXIT_FAILURE.
 * 
 * @param error_message The message to display before exiting.
 */
void fatal_error(const char *error_message);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ERROR_H */
