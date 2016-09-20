#include "all.h"

#define N 1000

typedef struct tree_node* searchtree;
typedef int data_t;

struct tree_node {
    data_t data;
    searchtree left;
    searchtree right;
};

searchtree destroy(searchtree t)
{
    if (t != NULL) {
        destroy(t->left);
        destroy(t->right);
        free(t);
    }
    return NULL;
}

searchtree find(data_t d, searchtree t)
{
    if (t == NULL)
        return NULL;
    if (d < t->data)
        return find(d, t->left);
    if (d > t->data)
        return find(d, t->right);

    return NULL;
}

searchtree findmin(searchtree t)
{
    if (t == NULL)
        return NULL;
    else if (t->left == NULL)
        return t;
    else
        return findmin(t->left);
}

searchtree findmax(searchtree t)
{
    if (t == NULL)
        return NULL;
    else if (t->right == NULL)
        return t;
    else
        return findmax(t->right);
}

searchtree deletenode(data_t d, searchtree t)
{
    searchtree tmpnode;

    if (t == NULL) {
        fprintf(stderr, "not found data %d\n", d);
        return t;
    }
    if (d < t->data)
        t->left = deletenode(d, t->left);
    else if (d > t->data)
        t->right = deletenode(d, t->right);
    else if (t->left && t->right) {  /* two children */
        /* replace with smallest in right subtree */
        tmpnode = findmin(t->right);
        t->data = tmpnode->data;
        t->right = deletenode(tmpnode->data, t->right);
    } else { /* one or zero child */
        tmpnode = t;
        /* also handles 0 children */
        if (t->left == NULL)
            t = t->right;
        else if (t->right == NULL)
            t = t->left;
        free(tmpnode);
    }
    return t;
}

searchtree insert(data_t d, searchtree t)
{
    if (t == NULL) {
        t = (searchtree) malloc(sizeof(struct tree_node));
        if (t == NULL) {
            fprintf(stderr, "malloc error");
            exit(1);
        }
        t->data = d;
        t->left = t->right = NULL;
    } else if (d < t->data) {
        t->left = insert(d, t->left);
    } else if (d > t->data) {
        t->right = insert(d, t->right);
    }
    /* else if d is in the tree already, do nothing */

    return t;
}

void print_tree(searchtree t)
{
    int i;
    static int level = 0;

    if (t == NULL) {
        printf("NULL\n");
        level -= 1;
    } else {
        printf("%d\n", t->data);
        if (t->left || t->right) {
            /* print left subtree */
            for (i = 0; i < 4 * level; ++i)
                if (i % 4 == 0)
                    printf("│");
                else 
                    printf(" ");
            printf("├── ");
            level += 1;
            print_tree(t->left);

            /* print right subtree */
            for (i = 0; i < 4 * level; ++i)
                if (i % 4 == 0)
                    printf("│");
                else 
                    printf(" ");
            printf("└── ");
            level += 1;
            print_tree(t->right);
            level -= 1;
        } else {
            level -= 1;
        }
    }
}

searchtree create_from_array(data_t datas[], int n)
{
    int i;
    searchtree t;

    t = NULL;
    for (i = 0; i < n; ++i)
        t = insert(datas[i], t);
    return t;
}

int main()
{
    int datas[N], i;
    searchtree t;
    time_t tt;

    printf("%lu\n", tt = time(0));
    puts("creating tree...");
    srand(time(0));
    for (i = 0; i < N; ++i)
        datas[i] = rand() % N;
    t = create_from_array(datas, N);
    printf("Tree:\n");
    print_tree(t);
    printf("%lu\n", time(0) - tt);

    puts("destroying tree...");
    t = destroy(t);
    printf("Tree = ");
    print_tree(t);
    return 0;
}
