#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree {
	char data;
	struct tree *lchild, *rchild;
	int ltag, rtag;
};

int power(int a, int n)
{
	int s;

	s = a;
	while (--n > 0)
		s *= a;
	return s;
}

int deepth(int n)
{
	int i;

	for (i = 1; ; ++i)
		if (n <= power(2, i) - 1)
			return i;
}

struct tree *create_tree(char *s, int deep)
{
	int dtmp;
	struct tree *t;

	if (*s == '\0')
		return NULL;
	if ((t = (struct tree *)malloc
				(sizeof(struct tree))) == NULL)
		exit(1);
	if (deep == 1) {
		t->data = *s;
		t->lchild = t->rchild = NULL;
		t->ltag = t->rtag = 0;
	} else {
		if (strlen(s) == 1) {
			t->data = *s;
			t->lchild = t->rchild = NULL;
			return t;
		}
		if ((t->lchild = create_tree(s, deep - 1)) != NULL)
			t->ltag = 1;
		else
			t->ltag = 0;
		t->data = *(s + (power(2, deep) - 2) / 2);
		s += power(2, deep) / 2;
		dtmp = deepth(strlen(s));
		if (deep - 1 > dtmp)
			deep = dtmp;
		else
			--deep;
		if ((t->rchild = create_tree(s, deep)) != NULL)
			t->rtag = 1;
		else
			t->rtag = 0;
	}
	return t;
}

struct tree *threading(struct tree *t)
{
	struct tree *pre;

	if (t == NULL)
		return NULL;
	pre = threading(t->lchild);
	if (pre == NULL)
		return t;
	else
		if (t->ltag == 0)
			t->lchild = pre;
		if (pre->rtag == 0)
			pre->rchild = t;
	return threading(t->rchild);
}

struct tree *getnext(struct tree *t)
{
	if (t->rtag == 0) {
		if (t->rchild == NULL)
			return t;
		return t->rchild;
	} else {
		t = t->rchild;
		while (t->ltag == 1)
			t = t->lchild;
	}
	return t;
}

void pr_thrtree(struct tree *t)
{
	while (t->ltag != 0)
		t = t->lchild;
	while (t->rchild != NULL) {
		printf("%-2c", t->data);
		t = getnext(t);
	}
	printf("%-2c\n", t->data);
}

void pr_tree(struct tree *t)
{
	if (t->lchild != NULL && t->ltag == 1)
		pr_tree(t->lchild);
	printf("%-2c", t->data);
	if (t->rchild != NULL && t->rtag == 1)
		pr_tree(t->rchild);
}

int main()
{
	struct tree *t;
	char s[] = "abcdefghijk";

	printf("creating tree by string `%s`...\n", s);
	t = create_tree(s, deepth(strlen(s)));
	printf("print tree:\n");
	pr_tree(t);
	putchar('\n');
	threading(t);
	printf("threading tree...\n");
	printf("print threaded tree:\n");
	pr_thrtree(t);
}
