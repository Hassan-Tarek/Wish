#define _GNU_SOURCE

#ifndef BUILTINS_EXECUTOR_H
#define BUILTINS_EXECUTOR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <unistd.h>

#include "command.h"
#include "env.h"
#include "path.h"
#include "io.h"
#include "error.h"

void execute_builtin_command(Command *command);
void execute_cd_command(Command *command);
void execute_exit_command(Command *command);
void execute_pwd_command(Command *command);
void execute_echo_command(Command *command);
void execute_export_command(Command *command);
void execute_unset_command(Command *command);
void execute_env_command(Command *command);
void execute_help_command(Command *command);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BUILTINS_EXECUTOR_H */
