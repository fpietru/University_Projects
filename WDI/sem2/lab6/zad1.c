#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int klucz;
    struct node *lewy, *prawy;
} node, *pnode;

pnode newnode(int k) {
    pnode v = malloc(sizeof(node));
    v->klucz = k;
    v->lewy = v->prawy = NULL;
    return v;
}

void insert(pnode *v, int k) {
    if ((*v) == NULL) {
        (*v) = newnode(k);
        return;
    }
    if (k < (*v)->klucz)
        insert(&((*v)->lewy), k);
    else
        insert(&((*v)->prawy), k);
}

void printBST(pnode v) {
    if (v == NULL) return;
    printBST(v->lewy);
    printf("%d ", v->klucz);
    printBST(v->prawy);
}

int min(pnode v) {
    if (v == NULL) return 1e9+7;
    else {
        int a = v->klucz;
        int b = min(v->lewy);
        return (a <= b ? a : b);
    }
}

// wypisz wszystkie klucze które NIE występują w drzewie BST (liczby całkowite z zakresu [min, max] z drzewa)
void wypisz(pnode v, int *mx) {
    if (v->lewy != NULL) wypisz(v->lewy, mx);
    for (int i=(*mx)+1; i<v->klucz; i++)
        printf("%d ", i);
    (*mx) = v->klucz;
    if (v->prawy != NULL) wypisz(v->prawy, mx);
}

int main () {
    pnode root = NULL;

    insert(&root, 8);
    insert(&root, 10);
    insert(&root, 4);
    insert(&root, 2);
    insert(&root, 6);
    insert(&root, 11);
    insert(&root, 3);

    printBST(root);
    printf("\n");
    int mx = min(root);
    wypisz(root, &mx);

    return 0;
}