#define _GNU_SOURCE

#ifndef BUILTINS_H
#define BUILTINS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <stdbool.h>

#define BUILTIN_COMMAND_NUM 8

typedef enum {
    NONE,
    CD,
    PATH,
    PWD,
    ECHO,
    EXIT
} BuiltinType;

extern const char *builtin_commands[BUILTIN_COMMAND_NUM];

bool is_valid_builtin_command(const char *command_name);
BuiltinType get_builtin_type(const char *command_name);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BUILTINS_H */
