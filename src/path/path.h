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

extern char *path_list[MAX_PATHS];
extern size_t paths_count;

void init_path_list();
void add_path(const char *path);
void free_path_list();

char *find_executable_in_path(const char *command_name);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PATH_H */
