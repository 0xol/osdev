#ifndef VIZ_INCLUDE_STDIO_H
#define VIZ_INCLUDE_STDIO_H

#include <stdint.h>

typedef __SIZE_TYPE__ size_t;

#define NULL ((char *)0)
#define EOF (-1)

extern char putchar_set;

extern int (*putchar)(char c);
int puts(const char* c);
#define printf printf_
int printf_(const char* format, ...);

#endif