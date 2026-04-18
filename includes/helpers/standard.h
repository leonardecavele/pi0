#ifndef STANDARD_H
#define STANDARD_H

#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

uint32_t strlen(const uint8_t *s);
int strcmp(const uint8_t *s1, const uint8_t *s2);
int strncmp(const uint8_t *s1, const uint8_t *s2, uint32_t len);
void *memset(void *s, int c, uint32_t n);
uint32_t atoui(const char *s);
void strcpy(char *dst, const char *src, uint32_t max_len);
void *memcpy(void *dst, const void *src, size_t n);
void sleep(void);

#endif
