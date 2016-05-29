#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct glist {
	int atom;
	struct glist *head;
	struct glist *tail;
};

int check_gl(const char *s)
{
	int n;

	n = 0;
	while (*s) {
		if (*s == '(')
			++n;
		else if (*s == ')')
			--n;
		++s;
	}
	if (n != 0)
		return 0;
	else
		return 1;
}

int geti(const char *s) // atoi()
{
	int n;

	n = 0;
	while (isdigit(*s))
		n = n * 10 + *s++ - '0';
	return n;
}

char *getail(const char *s) // get tail pointor of list in s
{
	int m;

	if (*s == '(') {
		m = 0;
		while (*s) {
			if (*s == '(')
				++m;
			else if (*s == ')')
				--m;
			if (m == 0)
				break;
			++s;
		}
	} else {
		while (*s) {
			if (*s == ',' || *s == ')')
				break;
			++s;
		}
	}
	if (*s == ',')
		return (char *)s + 1;
	else
		return (char *)s;
}

struct glist *create_gl(char *s)
{
	char *t;
	struct glist *gl;

	if ((gl = (struct glist *)
				malloc(sizeof(struct glist))) == NULL)
		return NULL;
	switch (*s) {
		case '(':
			gl->head = create_gl(s + 1);
			t = getail(s);
			gl->tail = create_gl(t + 1);
			break;
		case ',':
			free(gl);
			gl = create_gl(s + 1);
			break;
		case '\0':
			free(gl);
			gl = NULL;
			break;
		case ')':
			gl->head = (struct glist *)0x1; // for null list ()
			gl->tail = NULL;
			break;
		default:
			gl->atom = geti(s);
			gl->head = NULL;
			t = getail(s);
			gl->tail = create_gl(t);
	}
	return gl;
}

void print_gl(struct glist *gl)
{
	static char c = 0;

	if (gl != NULL) {
		if (gl->head == NULL) {
			printf("%d, ", gl->atom);
			c = ' ';
		} else if (gl->head == (struct glist *)0x1) {
		} else {
			if (c == ')')
				putchar(' ');
			putchar('(');
			print_gl(gl->head);
			if (c == ' ')
				printf("\b\b");
			putchar(c = ')');
		}
		print_gl(gl->tail);
	}
}

int main(void)
{
	char s[40];
	struct glist *gl;

	strcpy(s, "((),(),(1,2,(3,4),()),(6,7))");
	if (!check_gl(s))
		exit(1);
	gl = create_gl(s);
	print_gl(gl);
	putchar('\n');

	exit(0);
}
