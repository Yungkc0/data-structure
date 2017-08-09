/*
input:  1 2 3 4 5
        1 7 6 5 9
output: 3 0 0 0 4
   */
#include "all.h"

typedef struct listNode {
    int data;
    struct listNode *next;
} Node;

Node *makeList(int nums[], int n);
Node *sumOfTwoLinkedList(Node *l1, Node *l2);

int main() {
    int n = 7;
    int a[] = {
        2, 0, 0, 0, 7, 0, 1
    };
    int b[] = {
        7, 9, 9, 9, 9, 9, 9
    };
    Node *list1 = makeList(a, n);
    Node *list2 = makeList(b, n);
    Node *ans = sumOfTwoLinkedList(list1, list2);
    while (ans) {
        printf("%-2d", ans->data);
        ans = ans->next;
    }
    putchar('\n');
    return 0;
}

Node *makeList(int nums[], int n) {
    Node *ret = NULL;
    for (int i = n-1; i >= 0; i--) {
        Node *node = malloc(sizeof(Node));
        node->data = nums[i];
        node->next = ret;
        ret = node;
    }
    return ret;
}

Node *sumOfTwoLinkedList(Node *l1, Node *l2) {
    Node *p, *q, *ans, *pre;
    if (l1 == NULL)
        return l2;
    else if (l2 == NULL)
        return l1;

    ans = malloc(sizeof(Node));
    ans->data = l1->data + l2->data;
    p = pre = ans;

    while ((l1 = l1->next) && (l2 = l2->next)) {
        int n = l1->data + l2->data;
        q = malloc(sizeof(Node));
        pre->next = q;
        q->data = n % 10;
        if (n < 9) {
            p = q;
        } else if (n > 9) {
            p->data += 1;
            for (p = p->next; p != q; p = p->next)
                p->data = 0;
        }
        pre = q;
    }

    if (ans->data > 9) {
        q = malloc(sizeof(Node));
        q->data = 1;
        ans->data -= 10;
        q->next = ans;
        ans = q;
    }

    return ans;
}
