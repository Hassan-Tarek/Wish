#include "redirect.h"

RedirectInfo *create_redirect(void) {
    RedirectInfo *redir = malloc(sizeof(RedirectInfo));
    if (!redir)
        fatal_error("Failed to allocate memory for RedirectInfo!");

    redir->file = NULL;
    redir->redirect_type = REDIR_NONE;

    return redir;
}

void free_redirect(RedirectInfo *redirect) {
    if (!redirect) return;

    free(redirect->file);
    redirect->file = NULL;

    free(redirect);
    redirect = NULL;
}

bool setup_redirects(RedirectInfo *redirects[], size_t max_redirects) {
    for (size_t i = 0; i < max_redirects; i++) {
        RedirectInfo *redirect = redirects[i];
        if (!redirect || !redirect->file || redirect->redirect_type == REDIR_NONE) 
            continue;

        int fd;
        switch(redirect->redirect_type) {
            case REDIR_INPUT:
                fd = open(redirect->file, O_RDONLY);
                if (fd < 0) { print_error_message("input redirect"); return false; }
                if (dup2(fd, STDIN_FILENO) < 0) { print_error_message("dup2 input"); return false; }
                close(fd);
                break;

            case REDIR_OUTPUT:
                fd = open(redirect->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) { print_error_message("output redirect"); return false; }
                if (dup2(fd, STDOUT_FILENO) < 0) { print_error_message("dup2 output"); return false; }
                close(fd);
                break;

            case REDIR_OUTPUT_APPEND:
                fd = open(redirect->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd < 0) { print_error_message("output append redirect"); return false; }
                if (dup2(fd, STDOUT_FILENO) < 0) { print_error_message("dup2 output append"); return false; }
                close(fd);
                break;

            case REDIR_ERROR:
                fd = open(redirect->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) { print_error_message("error redirect"); return false; }
                if (dup2(fd, STDERR_FILENO) < 0) { print_error_message("dup2 error"); return false; }
                close(fd);
                break;

            case REDIR_ERROR_APPEND:
                fd = open(redirect->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd < 0) { print_error_message("error append redirect"); return false; }
                if (dup2(fd, STDERR_FILENO) < 0) { print_error_message("dup2 error append"); return false; }
                close(fd);
                break;

            default:
                break;
        }
    }

    return true;
}
