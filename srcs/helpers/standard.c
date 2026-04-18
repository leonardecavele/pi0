#include "helpers/standard.h"

extern uint32_t strlen(const uint8_t *s)
{
	int	i = 0;

	while (*s++)
		i++;
	return (i);
}

extern int strcmp(const uint8_t *s1, const uint8_t *s2)
{
	while (*s1 && *s1 == *s2) { s1++; s2++; }
	return *s1 - *s2;
}

extern int strncmp(const uint8_t *s1, const uint8_t *s2, uint32_t len)
{
	while (len && *s1 && *s1 == *s2) { s1++; s2++; len--; }
	if (len == 0) return 0;
	return *s1 - *s2;
}

extern void *memset(void *s, int c, uint32_t n)
{
	uint8_t *p = (uint8_t *)s;
	while (n--)
		*p++ = (uint8_t)c;
	return s;
}

extern uint32_t atoui(const char *s)
{
	uint32_t	n;

	n = 0;
	while (*s >= '0' && *s <= '9') {
		n = (n * 10u) + (uint32_t)(*s - '0');
		s++;
	}
	return (n);
}

extern void	strcpy(char *dst, const char *src, uint32_t max_len)
{
	uint32_t	i;

	i = 0;
	while (i + 1u < max_len && src[i]) {
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

extern void sleep(void)
{
	__asm__ volatile ("wfi");
}

extern void	*memcpy(void *dst, const void *src, uint64_t n)
{
	while (n--)
		((uint8_t *)dst)[n] = ((uint8_t *)src)[n];
	return (dst);
}
