#define _GNU_SOURCE

#ifndef EXECUTOR_H
#define EXECUTOR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "../command/command.h"
#include "../builtin/builtin.h"
#include "../external/external.h"
#include "../util/fd_backup.h"
#include "../error/error.h"

/**
 * @brief Executes a single command (builtin or external).
 * 
 * Redirects are applied before execution and restored afterward.
 * 
 * @param command The command to execute. If NULL, returns -1.
 * 
 * @return The exit status of the command, or -1 on error.
 */
int execute_command(Command *command);

/**
 * @brief Executes a group of commands connected by pipes.
 * 
 * For example: `ls | grep foo | wc -l`
 * 
 * @param group The CommandGroup containing the piped commands.
 *              Must contain at least 2 commands.
 * 
 * @return The exit status of the last command in the pipeline, or -1 on error.
 */
int execute_pipeline(CommandGroup *group);

/**
 * @brief Executes a list of command groups separated by ';'.
 * 
 * For example: `ls -l | grep txt; echo hi; pwd`
 * Each CommandGroup may itself contain a pipeline.
 * 
 * @param list The CommandGroupList to execute.
 * 
 * @return The exit status of the last executed command, or -1 on error.
 */
int execute_command_group_list(CommandGroupList *list);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* EXECUTOR_H */
