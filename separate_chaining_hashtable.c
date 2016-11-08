#include "all.h"

#define TABLESIZE_MIN 1
#define MAX           400 

typedef int data_t;
typedef struct listnode* list;
typedef struct hashtbl*  hashtable;

struct listnode {
    data_t data;
    struct listnode *next;
};

struct hashtbl {
    int tablesize;
    list lists[0];
};

static int hash(data_t d, int tablesize)
{
    return (d % tablesize);
}

hashtable init_table(int tablesize)
{
    hashtable h;

    if (tablesize < TABLESIZE_MIN)
        return NULL;

    h = (hashtable) malloc(sizeof(struct hashtbl)
            + tablesize * sizeof(list));
    if (h == NULL)
        return NULL;
    h->tablesize = tablesize;

    return h;
}

list find(data_t d, hashtable h)
{
    list l;

    l = h->lists[hash(d, h->tablesize)];
    while (l != NULL && l->data != d)
        l = l->next;

    return l;
}

int insert(data_t d, hashtable h)
{
    int pos;
    list l, tmp, node;

    pos = hash(d, h->tablesize);
    l = h->lists[pos];
    while (l != NULL && l->data != d) {
        tmp = l;
        l = l->next;
    }
    if (l == NULL) {
        node = (list) malloc(sizeof(struct listnode));
        if (node == NULL)
            return 0;
        node->data = d;
        node->next = NULL;
        if (h->lists[pos] == NULL)
            h->lists[pos] = node;
        else
            tmp->next = node;
    }

    return 1;
}

void delete(data_t d, hashtable h)
{
    int pos;
    list l, tmp;

    pos = hash(d, h->tablesize);
    tmp = l = h->lists[pos];
    while (l != NULL && l->data != d) {
        tmp = l;
        l = l->next;
    }
    if (l != NULL) {
        if (tmp == l)
            h->lists[pos] = l->next;
        else
            tmp->next = l->next;
        free(l);
    }
}

static inline void print_list(list l)
{
    while (l != NULL) {
        printf("%-4d", l->data);
        l = l->next;
    }
}

void print_table(hashtable h)
{
    int i;

    for (i = 0; i < h->tablesize; ++i) {
        printf("%3d: ", i);
        print_list(h->lists[i]);
        putchar('\n');
    }
}

int main()
{
    int datas[MAX], i;
    hashtable h;

    srand(time(0));
    for (i = 0; i < MAX; ++i)
        datas[i] = rand() % MAX;
    h = init_table(37); /* primer */
    for (i = 0; i < MAX; ++i)
        insert(datas[i], h);

    print_table(h);

    return 0;
}
