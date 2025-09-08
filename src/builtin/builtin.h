#define _GNU_SOURCE

#ifndef BUILTIN_H
#define BUILTIN_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "../util/builtin_type.h"
#include "../error/error.h"
#include "../io/io.h"

struct Command;


typedef void (*BuiltinFunc)(struct Command *);

typedef struct {
    const BuiltinType builtin_type;
    BuiltinFunc builtin_func;
} Builtin;


bool is_valid_builtin_command(const char *command_name);
BuiltinType get_builtin_type(const char *command_name);

void execute_builtin_command(struct Command *command);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BUILTIN_H */
