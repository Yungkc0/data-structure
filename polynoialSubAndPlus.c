#include <stdio.h>
#include <stdlib.h>

typedef struct termNode polynomial;
typedef struct termNode {
    double coef;
    int    exp;
    struct termNode* next;
} termNode;

void print(polynomial* p);
void destroy(polynomial* p);
polynomial* create(void);
polynomial* subtract(polynomial* a, polynomial* b);
polynomial* plus(polynomial* a, polynomial* b);

int main() {
    polynomial* polyA;
    polynomial* polyB;
    polynomial* polyC;

    puts("Input Polynomial A");
    polyA = create();
    puts("Input Polynomial B");
    polyB = create();

    puts("A - B");
    polyC = subtract(polyA, polyB);
    print(polyC);
    destroy(polyC);
    puts("A + B");
    polyC = plus(polyA, polyB);
    print(polyC);

    return 0;
}

void print(polynomial* p) {
    polynomial* htmp = p;
    if (p == NULL)
        return;
    while (htmp != NULL) {
        if (htmp != p)
            printf(" + ");
        printf("%.2lfx^%d", htmp->coef, htmp->exp);
        htmp = htmp->next;
    }
    putchar('\n');
}

void destroy(polynomial* p) {
    polynomial* tmp  = p;
    polynomial* htmp = tmp;
    while (tmp != NULL) {
        htmp = tmp;
        tmp = tmp->next;
        free(htmp);
    }
}

static polynomial* insert(polynomial* p, int coef, int exp) {
    polynomial* term;
    polynomial* tmp;
    polynomial* htmp;

    if (coef == 0)
        return p;
    term = malloc(sizeof(termNode));
    if (term == NULL)
        return p;
    term->coef = coef;
    term->exp = exp;
    term->next = NULL;

    if (p == NULL) {    /* Polynomial is NULL. */
        return term;
    } else if (exp > p->exp) {
        term->next = p;
        return term;
    } else if (exp == p->exp) {
        free(term);
        return p;
    }
    htmp = tmp = p;
    while (tmp->next != NULL && exp < tmp->exp) {
        htmp = tmp;
        tmp  = tmp->next;
    }
    if (exp < tmp->exp) {
        tmp->next = term;
    } else if (exp == tmp->exp) {
        free(term);
        return p;
    } else {
        htmp->next = term;
        term->next = tmp;
    }
    return p;
}

polynomial* create(void) {
    int coef, exp;
    polynomial* p = NULL;
    while (1) {
        printf("Input coef and exp: ");
        scanf("%d%d", &coef, &exp);
        if (coef == 0)
            break;
        p = insert(p, coef, exp);
        print(p);
    }
    return p;
}

polynomial* subtract(polynomial* a, polynomial* b) {
    polynomial* c = NULL;

    while (a != NULL && b != NULL) {
        if (a->exp == b->exp) {
            if (a->coef - b->coef != 0.0)
                c = insert(c, a->coef - b->coef, a->exp);
            a = a->next;
            b = b->next;
        } else if (a->exp > b->exp) {
            c = insert(c, a->coef, a->exp);
            a = a->next;
        } else {
            c = insert(c, -b->coef, b->exp);
            b = b->next;
        }
    }
    while (a != NULL) {
        c = insert(c, a->coef, a->exp);
        a = a->next;
    }
    while (b != NULL) {
        c = insert(c, -b->coef, b->exp);
        b = b->next;
    }

    return c;
}

polynomial* plus(polynomial* a, polynomial* b) {
    polynomial* c = NULL;

    while (a != NULL && b != NULL) {
        if (a->exp == b->exp) {
            if (a->coef + b->coef != 0.0)
                c = insert(c, a->coef + b->coef, a->exp);
            a = a->next;
            b = b->next;
        } else if (a->exp > b->exp) {
            c = insert(c, a->coef, a->exp);
            a = a->next;
        } else {
            c = insert(c, b->coef, b->exp);
            b = b->next;
        }
    }
    while (a != NULL) {
        c = insert(c, a->coef, a->exp);
        a = a->next;
    }
    while (b != NULL) {
        c = insert(c, b->coef, b->exp);
        b = b->next;
    }

    return c;
}
