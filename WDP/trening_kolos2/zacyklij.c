/*
Polecenie:
Napisz funkcję, która daną listę jednokierunkową przekształca
w listę cykliczną, ale z odwróconym kierunkiem wskaźników.
Możesz założyć, że dana lista jest poprawną listą jednokierunkową,
to znaczy ma koniec i nie zapętla się.
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

lista zacyklij(lista l) {
    lista pocz = l;
    lista nast = l->next;
    while (nast != NULL) {
        lista nast2 = nast->next;
        nast->next = l;
        l = nast;
        nast = nast2;
    }
    pocz->next = l;
    return l;
}

int main () {
    
    lista l = NULL;
    int n; scanf("%d", &n);
    for (int i=1; i<=n; i++) {
        int x; scanf("%d", &x);
        l = push(l, x);
    }

    wypisz(l);
    l = zacyklij(l);
    wypisz(l);

    return 0;
}