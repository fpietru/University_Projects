#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int val;
    struct node *prev, *next;
} node;

typedef struct lista {
    node *head, *tail;
} lista;

lista create_list() {
    lista res = {.head = NULL, .tail = NULL};
    return res;
}

bool empty(const lista l) {
    return (l.head == NULL);
}

int front(const lista l) {
    if (l.head == NULL)
        return -1;
    return l.head->val;
}

int back(const lista l) {
    if (l.tail == NULL)
        return -1;
    return l.tail->val;
}

void push_front(lista *l, int x) {
    node *n = (node*)malloc(sizeof(node));
    n->val = x;
    n->next = (*l).head;
    n->prev = NULL;
    if (!empty(*l)) {
        (*l).head->prev = n;
    } else {
        (*l).tail = n;
    }
    (*l).head = n;
}

void push_back(lista *l, int x) {
    node *n = (node*)malloc(sizeof(node));
    n->val = x;
    n->next = NULL;
    n->prev = (*l).tail;
    if (!empty(*l)) {
        (*l).tail->next = n;
    } else {
        (*l).head = n;
    }
    (*l).tail = n;
}

void wypisz(lista l) {
    printf("[ ");
    for (node *it=l.head; it != NULL; it = it->next) {
        printf("%d ", it->val);
    }
    printf("]\n");
}


int main () {

    lista l = create_list();
    push_front(&l, 1);
    push_front(&l, 2);
    push_front(&l, 3);
    push_front(&l, 4);
    push_back(&l, 10);
    push_back(&l, 11);
    push_back(&l, 12);
    push_back(&l, 13);

    wypisz(l);

    return 0;
}