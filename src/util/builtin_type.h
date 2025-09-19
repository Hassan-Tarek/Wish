#define _GNU_SOURCE

#ifndef BUILTIN_TYPE_H
#define BUILTIN_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @enum BuiltinType
 * @brief Enumeration of all supported built-in shell commands.
 *
 * This enum is used to classify and dispatch built-in commands
 * implemented directly by the shell rather than external programs.
 */
typedef enum {
    NONE,
    CD,
    EXIT,
    PWD,
    ECHO,
    EXPORT,
    UNSET,
    ENV,
    HELP
} BuiltinType;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BUILTIN_TYPE_H */
