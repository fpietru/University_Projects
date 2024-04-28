/*
    Zadaniem procedury jest znalezienie i zwrócenie jako wyniku liczby par kolejnych
    elementów tej listy, takich że klucze elementów należących do pary różnią się
    o liczbę parzystą (uwaga: każdy element listy oprócz pierwszego i ostatniego
    należy do dwóch par, które trzeba zbadać).
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

int procedura(pnode h) {
    int res = 0;
    while (h != NULL && h->next != NULL) {
        if ((h->wart - (h->next)->wart) % 2 == 0)
            res++;
        h = h->next;
    }
    return res;
}

int main () {
    pnode head = NULL;

    push(&head, 1);
    push(&head, 3);
    push(&head, 5);
    push(&head, 9);
    push(&head, 10);

    printf("%d\n", procedura(head));

    return 0;
}