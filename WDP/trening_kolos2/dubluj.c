/*
Polecenie:
Napisz funkcję dublującą elementy danej listy
jednokierunkowej. 
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct elem {
    int val;
    struct elem *next;
} elem;
typedef elem *lista;

lista push(lista l, int x) {
    lista nowy = (lista)malloc(sizeof(elem));
    if (nowy != NULL) {
        nowy->val = x;
        nowy->next = l;
    }
    return nowy;
}

void wypisz(lista l) {
    printf("[ ");
    while (l) {
        printf("%d ", l->val);
        l = l->next;
    }
    printf("]\n");
}

lista dubluj(lista l) {
    lista pocz = l;
    while (l) {
        lista nast = l->next;
        lista nowy = (lista)malloc(sizeof(elem));
        nowy->val = l->val;
        nowy->next = nast;
        l->next = nowy;
        l = nast;
    }
    return pocz;
}

int main () {
    
    lista l = NULL;
    int n; scanf("%d", &n);
    for (int i=1; i<=n; i++) {
        int x; scanf("%d", &x);
        l = push(l, x);
    }

    wypisz(l);
    l = dubluj(l);
    wypisz(l);

    return 0;
}