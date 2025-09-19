#define _GNU_SOURCE

#ifndef EXTERNAL_H
#define EXTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "../path/path.h"
#include "../error/error.h"

// Forward declaration to avoid circular include.
struct Command;

/**
 * @brief Checks whether a given command name refers to a valid external command.
 *
 * Looks up the command in the system PATH to determine whether
 * it can be executed as an external program.
 *
 * @param command_name The name of the command to check.
 * 
 * @return true if the command exists in PATH and is executable, false otherwise.
 */
bool is_valid_external_command(const char *command_name);

/**
 * @brief Executes an external command.
 *
 * Uses fork/execv to run the specified command in a child process.
 * The parent process waits for the child to complete and returns
 * the child’s exit status.
 *
 * @param command Pointer to a Command struct representing the external command.
 * 
 * @return Exit status of the executed command, or -1 on failure.
 */
int execute_external_command(struct Command *command);

/**
 * @brief Executes an external command directly without forking.
 *
 * @param command Pointer to a Command struct representing the external command.
 */
void execute_external_direct(struct Command *command);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* EXTERNAL_H */
