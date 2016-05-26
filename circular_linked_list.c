#include <stdio.h>
#include <stdlib.h>

struct cirlist {
	int data;
	struct cirlist *next;
} l;

int listlen(struct cirlist *l)
{
	int i;
	struct cirlist *tmp;

	for (i = 1, tmp = l->next; tmp != l; ++i)
		tmp = tmp->next;
	return i;
}

struct cirlist *init_list(struct cirlist *l, int n)
{
	struct cirlist *tmp, *s;
	size_t size, i;

	size = sizeof(struct cirlist);
	l = (struct cirlist *)malloc(size);
	l->data = 1;
	l->next = l;
	s = tmp = l;
	for (i = 2; i <= n; ++i) {
		s = (struct cirlist *)malloc(size);
		s->next = l;
		s->data = i;
		tmp->next = s;
		tmp = s;
	}
	return l;
}

struct cirlist *del_list(struct cirlist *l, int n)
{
	int len;
	struct cirlist *tmp, *pre;

	pre = tmp = l;
	len = listlen(l);
	if (len == 1 && n == l->data){
		free(l);
		return (l = NULL);
	}
	tmp = l->next;
	while (tmp != l) {
		if (tmp->data == n) {
			pre->next = tmp->next;
			free(tmp);
		}
		pre = tmp;
		tmp = tmp->next;
	}
	if (tmp->data == n) {
		pre->next = tmp->next;
		free(tmp);
		return pre->next;
	}
	return l;
}

void print_list(struct cirlist *l)
{
	struct cirlist *tmp;
	int len;

	tmp = l;
	len = listlen(l);
	for (; len > 0; --len) {
		printf("%3d", tmp->data);
		tmp = tmp->next;
	}
	putchar('\n');
}

int main()
{
	struct cirlist *h = NULL, *t;
	int len, nu, d;
	
	len = 41;
	nu = 1;
	h = init_list(h, len);
	t = h;
	while (len > 2) {
		if (nu == 3) {
			d = t->data;
			t = t->next;
			h = del_list(h, d);
			--len;
			nu = 1;
		} else {
			t = t->next;
			++nu;
		}
	}
	print_list(h);
	return 0;
}
