#define _GNU_SOURCE

#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../command/command.h"
#include "../builtin/builtin.h"
#include "../error/error.h"

int parse_input(char* input, const Command *command_list[]);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PARSER_H */
