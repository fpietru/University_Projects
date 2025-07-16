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

lista pop(lista l) {
    if (l == NULL) {
        return l;
    }
    lista n = l->next;
    free(l);
    return n;
}

lista reverse(lista l) {
    lista res = NULL;
    while (l) {
        res = push(res, l->val);
        l = pop(l);
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
    
    lista l = NULL;
    int n; scanf("%d", &n);
    for (int i=1; i<=n; i++) {
        int x; scanf("%d", &x);
        l = push(l, x);
    }

    wypisz(l);
    l = reverse(l);
    wypisz(l);

    return 0;
}