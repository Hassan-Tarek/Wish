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

/**
 * @brief Initializes the shell environment.
 *
 * Sets up environment variables, PATH list, and any
 * required state before running commands.
 */
void init_shell(void);

/**
 * @brief Runs the shell in iterative (interactive) mode.
 *
 * Continuously displays a prompt, reads user input,
 * parses it into commands, and executes them until exit.
 */
void run_iterative(void);

/**
 * @brief Runs the shell in batch mode.
 *
 * Reads commands from a specified file and executes them
 * sequentially, without showing an interactive prompt.
 *
 * @param filename Path to the batch file containing commands.
 */
void run_batch(const char *filename);

/**
 * @brief Cleans up shell resources before exiting.
 *
 * Frees allocated memory, restores environment, and ensures
 * that file descriptors or processes are properly closed.
 */
void cleanup_shell(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WISH_H */
