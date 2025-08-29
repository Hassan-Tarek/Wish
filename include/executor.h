#define _GNU_SOURCE

#ifndef EXECUTOR_H
#define EXECUTOR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "command.h"
#include "builtins_executor.h"
#include "external_executor.h"
#include "error.h"

void execute_command(Command *command);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* EXECUTOR_H */
