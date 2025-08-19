#define _GNU_SOURCE

#ifndef ERROR_H
#define ERROR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h>

void print_error_message(const char* error_message);
void fatal_error(const char* error_message);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ERROR_H */
