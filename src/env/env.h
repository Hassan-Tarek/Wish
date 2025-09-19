#define _GNU_SOURCE

#ifndef ENV_H
#define ENV_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../error/error.h"

/**
 * @brief Global environment variables list used by the shell.
 */
extern char **wish_environ;

/**
 * @brief Number of environment variables in ::wish_environ.
 */
extern size_t wish_environ_count;

/**
 * @brief Initialize the shell's internal environment.
 * 
 * Copies the current process environment variables into ::wish_environ.
 */
void init_wish_environ(void);

/**
 * @brief Set or update an environment variable.
 * 
 * @param name Name of the environment variable.
 * @param value Value to assign to the variable.
 * @param overwrite If non-zero, overwrite an existing variable.
 * 
 * @return 0 on success, non-zero on failure.
 */
int wish_setenv(const char *name, const char *value, int overwrite);

/**
 * @brief Remove an environment variable.
 * 
 * @param name Name of the environment variable to remove.
 * 
 * @return 1 if the variable was removed, 0 if it did not exist.
 */
int wish_unsetenv(const char *name);

/**
 * @brief Get the value of an environment variable.
 * 
 * @param name Name of the environment variable.
 * 
 * @return Pointer to the value string, or NULL if not found.
 */
char *wish_getenv(const char *name);

/**
 * @brief Free all memory allocated for ::wish_environ.
 * 
 * Should be called when the shell exits to prevent memory leaks.
 */
void free_wish_environ(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ENV_H */
