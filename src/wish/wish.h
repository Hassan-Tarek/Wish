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

#include "../io/io.h"
#include "../command/command.h"
#include "../parser/parser.h"
#include "../executor/executor.h"
#include "../env/env.h"
#include "../path/path.h"

#define MAX_COMMANDS 128

void init_shell(void);
void run_iterative(void);
void run_batch(const char *filename);
void cleanup_shell(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WISH_H */
