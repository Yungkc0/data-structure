#include <stdio.h>

char *strcpy(char *dest, const char *src)
{
	char *tmp = dest;

	while ((*tmp++ = *src++) != '\0')
		;
	return dest;
}

char *strncpy(char *dest, const char *src, size_t n)
{
	char *tmp = dest;

	for ( ; n >= 0; --n) {
		if ((*tmp = *src) != 0)
			src++;
		tmp++;
	}
	return dest;
}

size_t strlen(const char *s)
{
	const char *sc;

	for (sc = s; *sc != '\0'; ++sc)
		;
	return sc - s;
}

int strcmp(const char *s1, const char *s2)
{
	for ( ; *s1 == *s2; ++s1, ++s2)
		if (*s1 == '\0')
			return 0;
	return *s1 - *s2;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
	for ( ; n > 0; --n)
		if (*s1++ != *s2++)
			return *s1 - *s2;
	return 0;
}

char *strncat(char *dest, const char *src, size_t n)
{
	char *tmp = dest;

	while (*tmp != 0)
		tmp++;
	for ( ; n > 0; --n) {
		if ((*tmp = *src) != 0)
			src++;
		tmp++;
	}
	return dest;
}

char *strstr(const char *s, const char *t)
{
	size_t l1, l2;

	l2 = strlen(t);
	if (!l2)
		return (char *)s;
	l1 = strlen(s);
	while (l1 >= l2) {
		l1--;
		if (!strncmp(s, t, l2))
			return (char *)s;
		s++;
	}
	return NULL;
}

char *strdel(char *s, size_t pos, size_t len)
{
	size_t l;
	char *s1, *s2;

	l = strlen(s);
	if (pos >= 0 && pos <= l &&
			len >= 0 && len <= l - pos + 1) {
		s1 = s + pos;
		s2 = s + pos + len;
		while ((*s1++ = *s2++) != 0)
			;
		return s;
	} else {
		return NULL;
	}
}

int main(void)
{
	char c[20] = "abcdef";

	printf("%s\n", strdel(c, 0, 8));

	return 0;
}
