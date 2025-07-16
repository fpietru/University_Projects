/*
    Napisz procedurę, która wyszukuje w liście jednokierunkowej wszystkie elementy
    spełniające pewien warunek (który jest sprawdzany przez pewną osobną
    procedurę) i usuwa te elementy z listy.
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

int dirty(pnode h) {
    if (h->wart >= 100)
        return 1;
    return 0;
}

void clean(pnode *h) {
    while ((*h) != NULL) {
        pnode p = (*h);
        if (dirty(p)) {
            (*h) = (*h)->next;
            free(p);
        }
        else break;
    }
    if ((*h) == NULL)
        return;

    pnode st = (*h);
    while ((*h)->next != NULL) {
        pnode p = (*h)->next;
        while (p != NULL && dirty(p)) {
            pnode u = p;
            p = p->next;
            free(u);
        }
        if (p == NULL) {
            (*h)->next = NULL;
            break;
        }
        else {
            (*h)->next = p;
            (*h) = (*h)->next;
        }
    }
    
    (*h) = st;
}

int main () {
    pnode head = NULL;

    push(&head, 1);
    push(&head, 100);
    push(&head, 2);
    push(&head, 100);
    push(&head, 100);
    push(&head, 100);
    push(&head, 3);
    push(&head, 4);
    push(&head, 100);
    push(&head, 100);

    print(head);
    clean(&head);
    print(head);

    return 0;
}