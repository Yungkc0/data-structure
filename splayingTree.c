#include "all.h"

typedef int dataType;
typedef struct treeNode splayTree;
typedef struct treeNode {
    dataType data;
    struct treeNode* left;
    struct treeNode* right;
} treeNode;

void printTree(splayTree* t, int layer);
splayTree* createFromArray(dataType datas[], int n);
splayTree* insert(splayTree* t, dataType x);
splayTree* find(splayTree* t, dataType x);

int main() {
    const int N = 10;
    dataType datas[N];
    splayTree* tree = NULL;
    dataType x;

    srand(time(NULL));
    CREATE_ARRAY(datas, N, 100);
    tree = createFromArray(datas, N);
    if (tree == NULL)
        FatalError("Create tree error!");
    printTree(tree, 0);
    x = datas[rand() % N];
    printf("\n----Finding %d and splaying----\n", x);
    tree = find(tree, x);
    printTree(tree, 0);
}

splayTree* createFromArray(dataType datas[], int n) {
    splayTree* tree = NULL;
    for (int i = 0; i < n; ++i)
        tree = insert(tree, datas[i]);
    return tree;
}

splayTree* insert(splayTree* t, dataType x) {
    if (t == NULL) {
        t = malloc(sizeof(treeNode));
        t->left = NULL;
        t->right = NULL;
        t->data = x;
    } else if (x < t->data) {
        t->left = insert(t->left, x);
    } else if (x > t->data) {
        t->right = insert(t->right, x);
    }
    return t;
}

static splayTree* singleRotateLeft(splayTree* k2) {
    splayTree* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    return k1; /* New root. */
}

static splayTree* singleRotateRight(splayTree* k2) {
    splayTree* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    return k1;
}

static splayTree* doubleRotateLeft(splayTree* k3) {
    k3->left = singleRotateRight(k3->left);
    return singleRotateLeft(k3);
}

static splayTree* doubleRotateRight(splayTree* k3) {
    k3->right = singleRotateLeft(k3->right);
    return singleRotateRight(k3);
}

static splayTree* splay(splayTree* t, dataType x) {
    while (x != t->data) {
        if (x < t->data) {
            if (x < t->left->data) { /* Left zig-zig. */
                t = singleRotateLeft(t);
                t = singleRotateLeft(t);
            } else if (x > t->left->data) { /* Left zig-zag. */
                t = doubleRotateLeft(t);
            } else {
                t = singleRotateLeft(t);
            }
        } else if (x > t->data) {
            if (x > t->right->data) { /* Right zig-zig. */
                t = singleRotateRight(t);
                t = singleRotateRight(t);
            } else if (x < t->right->data) { /* Right zig-zag. */
                t = doubleRotateRight(t);
            } else {
                t = singleRotateRight(t);
            }
        }
    }
    return t;
}

static splayTree* findWithoutSplay(splayTree* t, dataType x) {
    if (t == NULL)
        return NULL;
    if (x < t->data)
        return findWithoutSplay(t->left, x);
    else if (x > t->data)
        return findWithoutSplay(t->right, x);
    else
        return t;
}

splayTree* find(splayTree* t, dataType x) {
    treeNode* node;
    if (t == NULL)
        return NULL;
    if ((node = findWithoutSplay(t, x)) != NULL)
        t = splay(t, x);
    return t;
}

void printTree(splayTree* t, int layer) {
    if (t == NULL) {
        for (int i = 0; i < layer; ++i)
            printf("    ");
        printf("NULL\n");
    } else {
        for (int i = 0; i < layer; ++i)
            printf("    ");
        printf("%d\n", t->data);
        printTree(t->left, layer + 1);
        printTree(t->right, layer + 1);
    }
}
