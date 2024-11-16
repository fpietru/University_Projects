
/*
    Napisz procedurę, która przetwarza listę jednokierunkową w ten sposób,
    że kolejność elementów zostaje odwrócona.
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

void print(pnode h) {
    while (h != NULL) {
        printf("%d ", h->wart);
        h = h->next;
    }
    printf("\n");
}

void przeszczep(pnode *n1, pnode *n2) {
    pnode pom = (*n1);
    (*n1) = (*n1)->next;
    pom->next = (*n2);
    (*n2) = pom;
}

void reverse(pnode *h) {
    pnode h2 = NULL;
    while ((*h) != NULL)
        przeszczep(h, &h2);
    (*h) = h2;
}

int main () {
    pnode head = NULL;
    push(&head, 1);
    push(&head, 2);
    push(&head, 5);
    push(&head, 8);
    push(&head, 7);

    print(head);
    reverse(&head);
    print(head);


    return 0;
}