#define _GNU_SOURCE

#ifndef PATH_H
#define PATH_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "command.h"
#include "io.h"
#include "error.h"

#define MAX_PATH_LENGTH 4096
#define MAX_PATHS 128

typedef struct {
    char *list[MAX_PATHS];
    size_t count;
} PathList;

PathList* create_path_list(void);
void add_path(PathList *path_list);
void remove_path(PathList *path_list);
void free_path_list(PathList *path_list);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PATH_H */
