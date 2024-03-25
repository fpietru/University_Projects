/*
    TODO: pozbyc sie ile w node i napisac funkcje ile roznych wart w drzewie
*/
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int klucz;
    int ile;
    int rozmiar;
    struct node *lewy, *prawy;
} node, *pnode;

pnode newnode(int k) {
    pnode v = malloc(sizeof(node));
    v->klucz = k;
    v->ile = 1;
    v->lewy = v->prawy = NULL;
}

void insert(pnode *v, int k) {
    if ((*v) == NULL) {
        (*v) = newnode(k);
        return;
    }
    if (k == (*v)->klucz)
        (*v)->ile++;
    else if (k < (*v)->klucz)
        insert(&((*v)->lewy), k);
    else
        insert(&((*v)->prawy), k);
}

void print(pnode v) {
    if (v == NULL) return;
    print(v->lewy);
    printf("[%d, %d] ", v->klucz, v->ile);
    print(v->prawy);
}

int rozmiar(pnode v) {
    if (v == NULL) return 0;
    return rozmiar(v->lewy) + 1 + rozmiar(v->prawy);
}

void zpliku(pnode *v) {
    FILE *fin = fopen("./dane.txt", "r");
    int k;
    while (fscanf(fin, "%d", &k) != EOF)
        insert(v, k);
    fclose(fin);
}

int max(int a, int b) { return (a >= b ? a : b); }

int wysokosc(pnode v) {
    if (v == NULL) return 0;
    return max(wysokosc(v->lewy), wysokosc(v->prawy)) + 1;
}

void usun_lisc_parz(pnode *v) {
    if ((*v) == NULL) return;
    if ((*v)->lewy == NULL && (*v)->prawy == NULL && ((*v)->klucz % 2 == 0)) {
        (*v) = NULL;
        return;
    }
    usun_lisc_parz(&((*v)->lewy));
    usun_lisc_parz(&((*v)->prawy));
}

int main () {
    pnode root = NULL;

    zpliku(&root);

    print(root);
    printf("\nRozmiar = %d\n", rozmiar(root));
    printf("Wysokosc = %d\n", wysokosc(root));

    usun_lisc_parz(&root);

    print(root);
    printf("\nRozmiar = %d\n", rozmiar(root));
    printf("Wysokosc = %d\n", wysokosc(root));


    return 0;
}