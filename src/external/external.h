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

#include "../command/command.h"
#include "../builtin/builtin.h"
#include "../external/external.h"
#include "../redirect/redirect.h"
#include "../path/path.h"
#include "../error/error.h"

bool is_valid_external_command(const char *command_name);

int execute_external_command(Command *command);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* EXTERNAL_H */
