/*
    Napisz procedurę dołączania elementu na koniec listy jednokierunkowej,
    dla której istnieje tylko zmienna wskazująca początek listy.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int wart;
    struct node *next;
} node, *pnode;

pnode newnode(int a) {
    pnode u = malloc(sizeof(node));
    u->wart = a;
    u->next = NULL;
    return u;
}

void push(pnode *h, int a) {
    pnode u = newnode(a);
    u->next = (*h);
    (*h) = u;
}

void push_back(pnode *h, int a) {
    if ((*h) == NULL)
        push(h, a);
    else {
        pnode pocz = (*h);
        while ((*h)->next != NULL)
            (*h) = (*h)->next;
        (*h)->next = newnode(a);
        (*h) = pocz;
    }
}

void print(pnode h) {
    while (h != NULL) {
        printf("%d ", h->wart);
        h = h->next;
    }
    printf("\n");
}

int main () {
    pnode head = NULL;

    push(&head, 812);
    push(&head, 32);
    push(&head, 81);
    print(head);


    push_back(&head, 12);
    push_back(&head, 4);

    print(head);

    return 0;
}