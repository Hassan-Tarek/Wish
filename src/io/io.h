#define _GNU_SOURCE

#ifndef IO_H
#define IO_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../error/error.h"

size_t INITIAL_CAPACITY = 256;

void print_prompt(void);
void print_message(FILE *out, const char *format, ...);
char* read_command(void);
char** read_commands_from_file(const char* filename);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IO_H */
