#define _GNU_SOURCE

#ifndef REDIRECT_H
#define REDIRECT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

#include "../error/error.h"

/**
 * @enum RedirectType
 * @brief Represents the type of I/O redirection applied to a command.
 *
 * This determines how standard input, output, or error streams
 * are redirected to/from files.
 */
typedef enum {
    REDIR_NONE,
    REDIR_INPUT,        // <
    REDIR_OUTPUT,       // >
    REDIR_OUTPUT_APPEND,// >>
    REDIR_ERROR,        // 2>
    REDIR_ERROR_APPEND  // 2>>
} RedirectType;

/**
 * @struct RedirectInfo
 * @brief Stores information about a single redirection.
 */
typedef struct {
    RedirectType redirect_type;
    char *file;
} RedirectInfo;

/**
 * @brief Allocates and initializes a new RedirectInfo structure.
 *
 * @return Pointer to the newly allocated RedirectInfo, or NULL on failure.
 */
RedirectInfo *create_redirect(void);

/**
 * @brief Frees a RedirectInfo structure and its associated resources.
 *
 * @param redirect Pointer to the RedirectInfo to free.
 */
void free_redirect(RedirectInfo *redirect);

/**
 * @brief Applies a list of redirections for the current process.
 *
 * Iterates over the given array of RedirectInfo structures and applies
 * valid redirections using system calls like open/dup2.
 *
 * @param redirects Array of RedirectInfo pointers.
 * @param max_redirects Maximum number of redirections in the array.
 * @return true if all redirections succeed, false if any fail.
 */
bool setup_redirects(RedirectInfo *redirects[], size_t max_redirects);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* REDIRECT_H */
