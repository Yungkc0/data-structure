#include <stdio.h>
#include <string.h>

void kmp_table(const char *w, int *table)
{
	size_t pos, cnd, len;

	len = strlen(w);
	pos = 2;
	cnd = 0;
	table[0] = -1;
	table[1] = 0;
	while (pos < len) {
		if (w[pos - 1] == w[cnd]) {
			table[pos] = cnd + 1;
			++cnd;
			++pos;
		} else if (cnd > 0) {
			cnd = table[cnd];
		} else {
			table[pos] = 0;
			++pos;
		}
	}
}

char *kmp_search(const char *s, const char *w)
{
	size_t l1 = strlen(s), l2 = strlen(w);
	int m, i, t[l2];

	kmp_table(w, t);
    m = i = 0;
	while (m + i < l1) {
		if (w[i] == s[m + i]) {
			if (i == l2 - 1)
				return (char *)s + m;
			++i;
		} else {
			if (t[i] > -1) {
				m = m + i - t[i];
				i = t[i];
			} else {
				m = m + i + 1;
				i = 0;
			}
		}
	}
	return (char *)s;
}

int main(void)
{
	char s[] = "abdefghijk";
	printf("%s\n", kmp_search(s, "def"));
}
