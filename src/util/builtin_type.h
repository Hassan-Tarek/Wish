#define _GNU_SOURCE

#ifndef BUILTIN_TYPE_H
#define BUILTIN_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

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
