#define _GNU_SOURCE

#ifndef EXECUTOR_H
#define EXECUTOR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>

bool is_valid_external_command(const char *command_name);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* EXECUTOR_H */
