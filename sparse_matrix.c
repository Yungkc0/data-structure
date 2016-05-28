#include <stdio.h>
#include <stdlib.h>

struct spmatrix {
	int col;
	int row;
	int **mx;
};

struct triple {
	int n;
	int col;
	int row;
	int (*mx)[3];
};

struct spmatrix *create_spmatrix(int (*mx)[], int row, int col)
{
	int (*m)[col];
	struct spmatrix *s;

	m = mx;
	if ((s = (struct spmatrix *)malloc(sizeof(struct spmatrix))) == NULL)
		return NULL;
	if ((s->mx = (int **)malloc(row * sizeof(int *))) == NULL)
		return NULL;
	s->col = col;
	s->row = row;
	for (row -= 1; row >= 0; --row)
		s->mx[row] = m[row];
	return s;
}

struct triple *compress(struct spmatrix *s)
{
	int i, j, m;
	size_t size;
	struct triple *t;

	size = sizeof(struct triple);
	if ((t = (struct triple *)malloc(size)) == NULL)
		return NULL;
	for (i = 0; i < s->row; ++i)
		for (j = 0; j < s->col; ++j)
			if (*(s->mx[i] + j) != 0)
				++t->n;
	if ((t->mx = (int (*)[])malloc(t->n * sizeof(int))) == NULL)
		return NULL;
	m = 0;
	for (i = 0; i < s->row; ++i)
		for (j = 0; j < s->col; ++j)
			if (*(s->mx[i] + j) != 0) {
				t->mx[m][0] = s->mx[i][j];
				t->mx[m][1] = i;
				t->mx[m][2] = j;
				++m;
			}
	t->col = s->col;
	t->row = s->row;
	return t;
}

void swap(int *a, int *b)
{
	int t;

	t = *a;
	*a = *b;
	*b = t;
}

void trans_spmx(struct triple *t)
{
	int i, j;

	for (i = 0; i < t->n; ++i) {
		for (j = i + 1; j < t->n - 1; ++j) {
			if (t->mx[i][2] > t->mx[j][2] || t->mx[i][1] > t->mx[j][1]) {
				swap(&t->mx[i][0], &t->mx[j][0]);
				swap(&t->mx[i][1], &t->mx[j][1]);
				swap(&t->mx[i][2], &t->mx[j][2]);
			}
		}
		swap(&t->mx[i][1], &t->mx[i][2]);
		swap(&t->col, &t->row);
	}
}

void pr_matrix(struct spmatrix *s)
{
	int i, j;

	for (i = 0; i < s->row; ++i) {
		for (j = 0; j < s->col; ++j) {
			printf("%-3d", s->mx[i][j]);
		}
		putchar('\n');
	}
}

void pr_triple(struct triple *t)
{
	int i;

	for (i = 0; i < t->n; ++i)
		printf("%-3d %-3d %-3d\n", t->mx[i][0], t->mx[i][1], t->mx[i][2]);
}

void pr_mxbytri(struct triple *t)
{
	int i, j, r, c, m;
	
	m = 0;
	r = t->mx[m][1];
	c = t->mx[m][2];
	for (i = 0; i < t->row; ++i) {
		for (j = 0; j < t->col; ++j) {
			if (i != r || j != c) {
				printf("0  ");
			} else {
				printf("%-3d", t->mx[m][0]);
				++m;
				r = t->mx[m][1];
				c = t->mx[m][2];
			}
		}
		putchar('\n');
	}
}

int main(void)
{
	struct spmatrix *s = NULL;
	struct triple *t = NULL;
	int mx[][9] = {
		0, 6, 0, 0, 23, 0, 0, 0, 4,
		0, 9, 23, 0, 0, 83, 0, 0, 0,
		0, 0, 0, 66, 2, 0, 0, 0, 34,
		88, 0, 5, 0, 0, 0, 0, 47, 0,
		0, 3, 0, 9, 0, 0, 99, 0, 0,
		7, 0, 0, 0, 0, 3, 0, 23, 0,
		5, 0, 0, 0, 0, 4, 0, 0, 0,
		0, 0, 0, 0, 56, 0, 0, 63, 0,
		37, 0, 0, 23, 0, 0, 0, 0, 27,
	};

	if ((s = create_spmatrix(mx, 9, 9)) == NULL)
		exit(1);
	printf("matrix(size %lu):\n", sizeof(mx));
	pr_matrix(s);
	if ((t = compress(s)) == NULL)
		exit(1);
	printf("compressed matrix(size %lu):\n", t->n * sizeof(int));
	printf(" v   i   j \n");
	pr_triple(t);
	printf("transposed matrix:\n");
	trans_spmx(t);
	pr_mxbytri(t);

	exit(0);
}
