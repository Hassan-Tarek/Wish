#define _GNU_SOURCE

#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "../command/command.h"
#include "../builtin/builtin.h"
#include "../error/error.h"

/**
 * @brief Parses a raw input string into a structured command group list.
 *
 * @param input The raw input string provided by the user (e.g., "ls -l | grep txt").
 *
 * @return Pointer to a dynamically allocated CommandGroupList representing
 *         the parsed commands. Returns NULL if parsing fails.
 */
CommandGroupList *parse_input(char *input);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PARSER_H */
