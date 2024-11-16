/*
    Franciszek Pietrusiak 458987
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int klucz;
    struct node *lewy, *prawy;
} node, *pnode;

pnode newnode(int k) {
    pnode v = malloc(sizeof(node));
    v->klucz = k;
    v->lewy = NULL;
    v->prawy = NULL;
}

// dodanie nowego wierzcholka do drzewa
void insert(pnode *v, int k) {
    if ((*v) == NULL) {
        (*v) = newnode(k);
        return;
    }
    if (k < (*v)->klucz)
        insert(&((*v)->lewy), k);
    else insert(&((*v)->prawy), k);
}

// wypisanie kluczy z drzewa w kolejnosci PRE-order
void printBST(pnode v) {
    if (v == NULL)
        return;
    printBST(v->lewy);
    printf("%d ", v->klucz);
    printBST(v->prawy);
}

// wczytanie ciagu kluczy z pliku "dane.txt" i podpiecie ich do poddrzewa wierzcholka v
void zpliku(pnode *v) {
    FILE* fin = fopen("./dane.txt", "r");
    int k;
    while (fscanf(fin, "%d", &k) != EOF)
        insert(v, k);
    fclose(fin);
}

// funkcja liczaca ile jest wierzcholkow w drzewie, ktore maja dokladnie jednego syna
int jedensyn(pnode v) {
    if (v == NULL)
        return 0;
    return jedensyn(v->lewy) + jedensyn(v->prawy) + ((v->lewy != NULL) ^ (v->prawy != NULL)); // ^ to logiczny XOR, daje 1 gdy v ma dokladnie jednego syna
}

int main () {
    pnode root = NULL;
    zpliku(&root);

    // printBST(root);
    printf("[ Wierzcholkow w drzewie, ktore maja dokladnie jednego syna jest: %d ]\n", jedensyn(root));

    return 0;
}