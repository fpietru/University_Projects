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
    else insert(&((*v)->prawy), k);
}

void printBST(pnode v) {
    if (v == NULL) return;
    printBST(v->lewy);
    printf("%d ", v->klucz);
    printBST(v->prawy);
}


// Funkcja, która sprawdza, czy w poddrzewie v występuje wierzchołek, którego lewy i prawy syn mają równe rozmiary poddrzew (większe od 0)
int funkcja(pnode v, int *mam) {
    if (v == NULL) {
        *mam = 0;
        return 0;
    }
    int mamL, mamP;
    int rL = funkcja(v->lewy, &mamL);
    int rP = funkcja(v->prawy, &mamP);
    if ((rL == rP && rL > 0) || mamL || mamP)
        *mam = 1;
    else *mam = 0;
    return rL + rP + 1;
}

int main() {
    pnode root = NULL;
    
    insert(&root, 8);
    insert(&root, 7);
    insert(&root, 6);
    insert(&root, 5);
    insert(&root, 4);
    insert(&root, 5);
    
    printBST(root);

    int mam = 0;
    funkcja(root, &mam);
    printf("\n%d\n", mam);

    return 0;
}