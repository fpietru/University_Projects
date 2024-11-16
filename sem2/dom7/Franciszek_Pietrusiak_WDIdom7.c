/*
    Franciszek Pietrusiak 458987
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int wart;
    struct node *next;
} node, *pnode;

void push(pnode *h, int a) {
    pnode u = malloc(sizeof(node));
    u->wart = a;
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

#define MxN 105
pnode G[MxN];
int M[MxN][MxN];

int main () {
    int n;
    scanf("%d", &n);
    for (int i=1; i<=n; i++)
        G[i] = NULL;

    while (1) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a == 0 && b == 0) // w poleceniu nie było zdefiniowane ile należy wczytać krawędzi. Niech wiersz 0 0 oznacza koniec wczytywania.
            break;
        // Założyłem, że graf jest nieskierowany, gdyby jednak chodziło o graf skierowany z krawędziami a->b, to należy wykomentować odpowiednie wiersze
        push(&G[a], b); // dodaję krawędź a->b do listy sąsiedztwa
        push(&G[b], a); // dodaję krawędź b->a do listy sąsiedztwa
        M[a][b]++; // dodaję krawędź a->b do macierzy sąsiedztwa
        M[b][a]++; // dodaję krawędź b->a do macierzy sąsiedztwa
    }

    printf("Lista Sasiedztwa:\n");
    for (int i=1; i<=n; i++) {
        printf("%d: ", i);
        print(G[i]);
    }

    printf("\nMacierz Sasiedztwa:\n");
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++)
            printf("%d ", M[i][j]);
        printf("\n");
    }

    return 0;
}
