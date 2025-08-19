#define _GNU_SOURCE

#ifndef WISH_H
#define WISH_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void init_shell(void);
void run_shell(void);
void cleanup_shell(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WISH_H */
