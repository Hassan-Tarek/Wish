#define _GNU_SOURCE

#ifndef COMMAND_H
#define COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../builtin/builtin.h"
#include "../external/external.h"
#include "../error/error.h"

// #define MAX_NAME_LENGTH 128
#define MAX_ARGS 128
// #define MAX_ARG_LENGTH 256
#define MAX_COMMANDS 128
// #define MAX_FILE_LENGTH 128
#define MAX_REDIRECTS 5


typedef enum {
    UNDEFINED,
    BUILTIN,
    EXTERNAL
} CommandType;

typedef struct {
    char *name;
    char *args[MAX_ARGS];
    size_t args_count;
    bool background;
    CommandType command_type;
    BuiltinType builtin_type;
    RedirectInfo *redirects[MAX_REDIRECTS];
} Command;

// extern Command *command_list[];

Command *create_command(void);
void free_command(Command *);

bool is_valid_command(const char *command_name);
CommandType get_command_type(const char *command_name);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* COMMAND_H */
