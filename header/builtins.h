#define _GNU_SOURCE

#ifndef BUILTINS_H
#define BUILTINS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "command.h"
#include "path.h"
#include "io.h"
#include "error.h"

typedef enum {
    NONE,
    CD,
    PATH,
    PWD,
    ECHO,
    EXIT
} BuiltinType;

extern const char *builtin_names[];
extern const size_t builtin_count;

bool is_valid_builtin_command(const char *command_name);
BuiltinType get_builtin_type(const char *command_name);

void execute_cd_command(Command *command);
void execute_path_command(Command *command);
void execute_pwd_command(Command *command);
void execute_echo_command(Command *command);
void execute_exit_command(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BUILTINS_H */
