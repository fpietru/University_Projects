/*
    Zadaniem procedury jest utworzenie drugiej listy, zawierającej kopie tych
    elementów, których klucze są liczbami parzystymi. Elementy tej listy należy
    tworzyć przy użyciu procedury malloc. Wskaźnik początku utworzonej listy ma
    być zwrócony jako wartość procedury.
    Kolejność elementów w utworzonej liście może być zgodna z ich uporządkowaniem
    w liście danej, lub odwrotna; napisz, jaka jest ta kolejność w napisanej przez siebie
    procedurze.
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

// procedura do zadania, odwraca kolejność
pnode copy_even(pnode h) {
    pnode res = NULL;
    while (h != NULL) {
        if (h->wart % 2 == 0) {
            pnode u = newnode(h->wart);
            u->next = res;
            res = u;
        }
        h = h->next;
    }
    return res;
}

// procedura do zadania, nie odwraca kolejności
pnode copy_even2(pnode h) {
    pnode st = NULL;
    pnode ed = NULL;
    while (h != NULL) {
        if (h->wart % 2 == 0) {
            pnode u = newnode(h->wart);
            if (st == NULL) {
                st = u;
                ed = u;
            }
            else {
                ed->next = u;
                ed = u;
            }
        }
        h = h->next;
    }
    return st;
}

int main () {
    pnode head = NULL;

    push(&head, 1);
    push(&head, 2);
    push(&head, 3);
    push(&head, 4);
    push(&head, 5);
    push(&head, 6);

    print(head);
    pnode h2 = copy_even(head);
    pnode h3 = copy_even2(head);
    print(h2);
    print(h3);

    return 0;
}