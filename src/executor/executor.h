#define _GNU_SOURCE

#ifndef EXECUTOR_H
#define EXECUTOR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "../command/command.h"
#include "../builtin/builtin.h"
#include "../external/external.h"
#include "../error/error.h"

void execute_command(Command *command);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* EXECUTOR_H */
