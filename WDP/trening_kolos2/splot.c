/*
Polecenie:
Napisz funkcję, która mając dane dwie listy jednokierunkowe,
splata je w jedną listę postaci:
1) pierwszy rekord pierwszej listy,
2) pierwszy rekord drugiej listy,
3) drugi rekord pierwszej listy,
4) drugi rekord drugiej listy,
itd.
Jeśli jedna z list jest dłuższa, to jej końcówka stanowi
końcówkę listy wynikowej. 
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

lista splot(lista l1, lista l2) {
    lista pocz = l1;
    int tura = 0;
    while (l1 && l2) {
        lista nl1 = l1->next;
        lista nl2 = l2->next;
        if (tura == 0) {
            l1->next = l2;
            l1 = nl1;
        } else {
            l2->next = l1;
            l2 = nl2;
        }
        tura ^= 1;
    }
    return pocz;
}

lista wczytaj(int n) {
    lista res = NULL;
    for (int i=1; i<=n; i++) {
        int x; scanf("%d", &x);
        res = push(res, x);
    }
    return res;
}

void wypisz(lista l) {
    printf("[ ");
    while (l) {
        printf("%d ", l->val);
        l = l->next;
    }
    printf("]\n");
}

int main () {
    
    int n, m; scanf("%d %d", &n, &m);
    lista l1 = wczytaj(n);
    lista l2 = wczytaj(m);

    wypisz(l1);
    wypisz(l2);
    wypisz(splot(l1, l2));

    return 0;
}