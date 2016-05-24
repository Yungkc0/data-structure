#include <stdio.h>
#include <ctype.h>

#define MAX 100

struct stack {
	int top;
	int data[MAX];
} optr, opnd;
char precede_table[8][8] = {
	{'0', '+', '-', '*', '/', '(', ')', '#'},
	{'+', '>', '>', '<', '<', '<', '>', '>'},
	{'-', '>', '>', '<', '<', '<', '>', '>'},
	{'*', '>', '>', '>', '>', '<', '>', '>'},
	{'/', '>', '>', '>', '>', '<', '>', '>'},
	{'(', '<', '<', '<', '<', '<', '=', '0'},
	{')', '>', '>', '>', '>', '0', '>', '>'},
	{'#', '<', '<', '<', '<', '<', '0', '='}
};

int optoi(int op)
{
	int opi;

	switch (op) {
		case '+':
			opi = 1; break;
		case '-':
			opi = 2; break;
		case '*':
			opi = 3; break;
		case '/':
			opi = 4; break;
		case '(':
			opi = 5; break;
		case ')':
			opi = 6; break;
		case '#':
			opi = 7; break;
		default:
			opi = 0;
	}
	return opi;
}

char precede(int op1, int op2) // compare precede of op1 and op2
{
	return precede_table[optoi(op1)][optoi(op2)];
}

int isoperator(int c)
{
	return (c == '-' || c == '*' ||
			c == '/' || c == '+' ||
			c == '#' || c == '(' ||
			c == ')') ? 1 : 0;
}

int operate(int a, int b, char op)
{
	switch (op) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			return a / b;
	}
}

int getop(struct stack *s)
{
	return s->data[s->top - 1];
}

int pop(struct stack *s)
{
	return s->top != 0 ? s->data[--s->top] : 0;
}

void push(struct stack *s, int c)
{
	s->data[s->top++] = c;
}

int main()
{
	char p;
	int c, prec, a, b;

	printf("input correct expression (e.g. 3*(7-2) ):\n");
	push(&optr, '#');
	c = getchar();
	while (c != '#' || getop(&optr) != '#') {
		if (c == '\n')
			c = '#';
		if (isoperator(c)) {
			switch (precede(getop(&optr), c)) {
				case '<':
					push(&optr, c);
					prec = c;
					c = getchar();
					break;
				case '=':
					pop(&optr);
					prec = c;
					c = getchar();
					break;
				case '>':
					p = pop(&optr);
					b = pop(&opnd);
					a = pop(&opnd);
					push(&opnd, operate(a, b, p));
					break;
			}
		} else if (isdigit(c)) {
			if (isoperator(prec))
				push(&opnd, c - '0');
			else
				push(&opnd, pop(&opnd) * 10 + c - '0');
			prec = c;
			c = getchar();
		} else {
			prec = c;
			c = getchar();
			continue;
		}
	}

	printf("result: %d\n", getop(&opnd));
	return 0;
}
