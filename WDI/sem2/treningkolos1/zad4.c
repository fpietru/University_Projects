/*
    Napisz procedurę, która otrzymuje dwie listy liniowe (parametrami procedury są
    wskaźniki początków obu list, nie używamy wskaźników końcowych elementów
    list) i która łączy te listy w jedną, tak, aby elementy z poszczególnych list
    występowały na przemian. Jeśli jedna z list jest krótsza, to „ogon” drugiej listy
    będzie „ogonem” listy połączonej.
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

pnode merge(pnode h, pnode h2) {
    node res_pocz;
    pnode res = &res_pocz;
    res->next = NULL;
    int turn = 0;
    while (1) {
        if (turn == 0) {
            if (h == NULL) {
                res->next = h2;
                break;
            }
            else przeszczep(&h, &(res->next));
        }
        else {
            if (h2 == NULL) {
                res->next = h;
                break;
            }
            else przeszczep(&h2, &(res->next));
        }
        turn = (turn + 1) % 2;
        res = res->next;
    }
    return (res_pocz.next);
}

int main () {
    pnode h = NULL;
    pnode h2 = NULL;

    push(&h, 1);
    push(&h, 3);
    push(&h, 5);
    push(&h, 7);
    push(&h, 9);
    push(&h, 11);
    
    push(&h2, 2);
    push(&h2, 4);
    push(&h2, 6);
    push(&h2, 8);
    push(&h2, 10);
    push(&h2, 12);
    push(&h2, 14);
    push(&h2, 16);


    print(h);
    print(h2);
    pnode h3 = merge(h, h2);
    print(h3);



    return 0;
}