#include "all.h"

typedef struct tree_node* avltree;
typedef int data_t;

struct tree_node {
    data_t data;
    avltree left;
    avltree right;
    int height;
};

static int height(avltree t)
{
    if (t != NULL)
        return t->height;
    else
        return -1;
}

avltree destroy(avltree t)
{
    if (t != NULL) {
        destroy(t->left);
        destroy(t->right);
        free(t);
    }
    return NULL;
}

avltree find(data_t d, avltree t)
{
    if (t == NULL)
        return NULL;
    if (d < t->data)
        return find(d, t->left);
    if (d > t->data)
        return find(d, t->right);
    else
        return t;
}

avltree findmin(avltree t)
{
    if (t == NULL)
        return NULL;
    else if (t->left == NULL)
        return t;
    else
        return findmin(t->left);
}

avltree findmax(avltree t)
{
    if (t == NULL)
        return NULL;
    else if (t->right == NULL)
        return t;
    else
        return findmax(t->right);
}

avltree deletenode(data_t d, avltree t)
{
    avltree tmpnode;

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

/* If k2 only has a left child, the function perform a rotate
 * between a node (k2) and its left child */
static avltree single_rotate_left(avltree k2)
{
    avltree k1;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;

    return k1; /* new root */
}

/* Perform like single_rotate_left */
static avltree single_rotate_right(avltree k2)
{
    avltree k1;

    k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;

    return k1;
}

/* If k3 only has a left child and k3's left child has a right
 * child. Do the left-right double rotation */
static avltree double_rotate_left(avltree k3)
{
    k3->left = single_rotate_right(k3->left);
    
    return single_rotate_left(k3);
}

static avltree double_rotate_right(avltree k3)
{
    k3->right = single_rotate_left(k3->right);

    return single_rotate_right(k3);
}

avltree insert(data_t d, avltree t)
{
    if (t == NULL) {
        t = (avltree) malloc(sizeof(struct tree_node));
        if (t == NULL) {
            fprintf(stderr, "malloc error");
            exit(1);
        }
        t->data = d;
        t->height = 0;
        t->left = t->right = NULL;
    } else if (d < t->data) {
        t->left = insert(d, t->left);
        if (height(t->left) - height(t->right) == 2) {
            if (d < t->left->data)
                t = single_rotate_left(t);
            else
                t = double_rotate_left(t);
        }
    } else if (d > t->data) {
        t->right = insert(d, t->right);
        if (height(t->right) - height(t->left) == 2) {
            if (d > t->right->data)
                t = single_rotate_right(t);
            else
                t = double_rotate_right(t);
        }
    }
    /* else if d is in the tree already, do nothing */

    t->height = max(height(t->left), height(t->right)) + 1;
    return t;
}

void print_tree(avltree t, int layer)
{
    if (t == NULL) {
        for (int i = 0; i < layer; ++i)
            printf("    ");
        printf("NULL\n");
    } else {
        for (int i = 0; i < layer; ++i)
            printf("    ");
        printf("%d\n", t->data);
        print_tree(t->left, layer + 1);
        print_tree(t->right, layer + 1);
    }
}

avltree create_from_array(data_t datas[], int n)
{
    int i;
    avltree t;

    t = NULL;
    for (i = 0; i < n; ++i)
        t = insert(datas[i], t);
    return t;
}

int main()
{
    const int N = 30;
    int datas[N], i;
    avltree t;

    puts("creating tree...");
    srand(time(0));
    for (i = 0; i < N; ++i)
        datas[i] = rand() % N;
    t = create_from_array(datas, N);
    print_tree(t, 0);

    puts("destroying tree...");
    t = destroy(t);
    print_tree(t, 0);
    return 0;
}
