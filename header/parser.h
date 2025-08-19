#define _GNU_SOURCE

#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "command.h"
#include "builtins.h"
#include "error.h"

typedef struct {
    Command *commands[MAX_COMMANDS];
    size_t count;
} ParsedCommands;

ParsedCommands *parse_input(const char* input);
void free_parsed_commands(ParsedCommands *commands);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PARSER_H */
