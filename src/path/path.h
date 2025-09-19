#define _GNU_SOURCE

#ifndef PATH_H
#define PATH_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>

#include "../env/env.h"

#define MAX_PATH_LENGTH 4096
#define MAX_PATHS 128

/**
 * @brief Global array holding parsed PATH directories.
 *
 * Each entry in path_list is a dynamically allocated string representing
 * one directory from the PATH environment variable.
 */
extern char *path_list[MAX_PATHS];

/**
 * @brief Number of valid entries in path_list.
 */
extern size_t paths_count;

/**
 * @brief Initializes the path_list from the PATH environment variable.
 *
 * Splits the PATH variable into directories and stores each one in
 * path_list. Updates paths_count accordingly.
 */
void init_path_list();

/**
 * @brief Adds a directory to the path_list.
 *
 * Duplicates and stores the given path into the global list.
 *
 * @param path Directory path to add.
 */
void add_path(const char *path);

/**
 * @brief Frees all memory used by path_list.
 *
 * Iterates over path_list, frees each stored directory string,
 * and resets paths_count to zero.
 */
void free_path_list();

/**
 * @brief Searches for an executable in the PATH directories.
 *
 * @param command_name The command name to search for (e.g., "ls").
 * @return Newly allocated string containing the absolute path to the executable,
 *         or NULL if not found.
 */
char *find_executable_in_path(const char *command_name);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PATH_H */
