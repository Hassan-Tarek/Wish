#define _GNU_SOURCE

#ifndef ENV_H
#define ENV_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

extern char **wish_environ;
extern size_t wish_environ_count;

void init_wish_environ();
void free_wish_environ();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ENV_H */
