/*
    Drzewo Czerwono-Czarne musi spełniać warunki:
    -[1] Każdy node jest czerwony lub czarny
    -[2] Korzeń jest czarny
    -[3] Każdy liść jest czarny
    -[4] Jeśli node jest czerwony, to obaj jego synowie są czarni
    -[5] Dla każdego node'a wszystkie ścieżki w jego poddrzewie do liści zawierają tyle samo czarnych wierzchołków
*/
#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

typedef struct node {
    int klucz;
    int kolor;
    struct node *lewy, *prawy, *p;
} node, *pnode;
pnode NIL, root;

void init() {
    NIL = (pnode)malloc(sizeof(node));
    NIL->kolor = BLACK;
    NIL->klucz = 0;
    NIL->lewy = NULL;
    NIL->prawy = NULL;
    NIL->p = NULL;
    root = NIL;
}

pnode newnode(int klu, int kol) {
    pnode u = (pnode)malloc(sizeof(node));
    u->klucz = klu;
    u->kolor = kol;
    u->lewy = NIL;
    u->prawy = NIL;
    u->p = NIL;
    return u;
}

void print(pnode v) {
    if (v == NIL) return;
    print(v->lewy);
    printf("%d [%d]\n", v->klucz, v->kolor);
    print(v->prawy);
}

void info() {
    printf("Korzeniem jest %d\n", root->klucz);
    print(root);
    printf("\n");
}

void rotacja_w_lewo(pnode x){
    pnode y = x->prawy;
    x->prawy = y->lewy; // przeszczep lewego syna y-ka jako prawego syna x-a
    if (y->lewy != NIL) // i jeśli on istnieje ...
        y->lewy->p = x; // ... to mu to powiedz
    y->p = x->p; // ojcem y-ka jest ojciec x-a
    if (x->p == NIL) // jeśli x był korzeniem ...
        root = y; // ... y jest korzeniem
    else if (x == x->p->lewy) // jeśli x był lewym synem swojego ojca ...
        x->p->lewy = y; // ... to teraz y nim jest
    else x->p->prawy = y; // jeśli x był prawym synem swojego ojca, to analogicznie
    y->lewy = x; // x staje się lewym synem y-ka
    x->p = y; // ... i mu o tym mówimy
}

void rotacja_w_prawo(pnode x) {
    pnode y = x->lewy;
    x->lewy = y->prawy; // przeszczep prawego syna y-ka jako lewego syna x-a
    if (y->prawy != NIL) // i jeśli on istnieje ...
        y->prawy->p = x; // ... to mu to powiedz
    y->p = x->p;
    if (x->p == NIL)
        root = y;
    else if (x == x->p->lewy)
        x->p->lewy = y;
    else x->p->prawy = y;
    y->prawy = x;
    x->p = y;
}

void napraw(pnode v) {
    while (v->p->kolor == RED) {
        if (v->p == v->p->p->lewy) { // jeśli ojciec v jest lewym synem swojego ojca
            pnode y = v->p->p->prawy; // y jest wujkiem v (prawym bratem ojca v)
            if (y->kolor == RED) { // Przypadek 1
                v->p->kolor = BLACK;
                y->kolor = BLACK;
                v->p->p->kolor = RED;
                v = v->p->p;
            }
            else { 
                if (v == v->p->prawy) { // Przypadek 2
                    v = v->p;
                    rotacja_w_lewo(v);
                } // Przypadek 3
                v->p->kolor = BLACK;
                v->p->p->kolor = RED;
                rotacja_w_prawo(v->p->p);
            }
        }
        else { // symetryczna sytuacja jeśli ojciec v jest prawym synem swojego ojca
            pnode y = v->p->p->lewy;
            if (y->kolor == RED) {
                v->p->kolor = BLACK;
                y->kolor = BLACK;
                v->p->p->kolor = RED;
                v = v->p->p;
            }
            else {
                if (v == v->p->lewy) {
                    v = v->p;
                    rotacja_w_prawo(v);
                }
                v->p->kolor = BLACK;
                v->p->p->kolor = RED;
                rotacja_w_lewo(v->p->p);
            }            
        }
    }
    root->kolor = BLACK; // upewnienie się, że warunek [2] jest spełniony
}

void insert(pnode v, int klu) {
    pnode y = NIL;
    while (v != NIL) {
        y = v;
        if (klu < v->klucz)
            v = v->lewy;
        else v = v->prawy;
    }
    pnode u = newnode(klu, RED);
    u->p = y;
    if (y == NIL)
        root = u;
    else if (u->klucz < y->klucz)
        y->lewy = u;
    else y->prawy = u;
    napraw(u);
}

int main () {

    init();

    insert(root, 2);
    info();

    insert(root, 4);
    info();
    
    insert(root, 6);
    info();
    
    insert(root, 1);
    info();


    return 0;
}