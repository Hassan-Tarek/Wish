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

typedef enum {
    REDIR_NONE,
    REDIR_INPUT,        // <
    REDIR_OUTPUT,       // >
    REDIR_OUTPUT_APPEND,// >>
    REDIR_ERROR,        // 2>
    REDIR_ERROR_APPEND  // 2>>
} RedirectType;

typedef struct {
    RedirectType redirect_type;
    char *file;
} RedirectInfo;

RedirectInfo *create_redirect(void);
void free_redirect(RedirectInfo *redirect);

bool setup_redirects(RedirectInfo *redirects[], size_t max_redirects);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* REDIRECT_H */
