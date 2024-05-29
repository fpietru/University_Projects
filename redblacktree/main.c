/*
    Drzewo Czerwono-Czarne musi spełniać warunki:
    -[1] Każdy node jest czerwony lub czarny
    -[2] Korzeń jest czarny
    -[3] Każdy liść jest czarny
    -[4] Jeśli node jest czerwony, to obaj jego synowie są czarni
    -[5] Dla każdego node'a wszystkie ścieżki wychodzące z niego do liści w jego poddrzewie zawierają tyle samo czarnych wierzchołków
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

void print(pnode v, int lvl) {
    if (v == NIL) return;
    print(v->lewy, lvl+1);
    for (int i=0; i<4*lvl; i++)
        printf(" ");
    printf("-> [%d %d]\n", v->klucz, v->kolor);
    print(v->prawy, lvl+1);
}

void info() {
    print(root, 0);
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

void napraw_insert(pnode v) {
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
    napraw_insert(u);
}

void przeszczep(pnode v, pnode u) {
    if (v->p == NIL)
        root = u;
    else if (v == v->p->lewy)
        v->p->lewy = u;
    else v->p->prawy = u;
    u->p = v->p;
}

pnode minimum(pnode v) {
    while (v->lewy != NIL)
        v = v->lewy;
    return v;
}

void napraw_delete(pnode x) {
    while (x != root && x->kolor == BLACK) {
        if (x == x->p->lewy) {
            pnode w = x->p->prawy;
            if (w->kolor == RED) {
                w->kolor = BLACK;
                x->p->kolor = RED;
                rotacja_w_lewo(x->p);
                w = x->p->prawy;
            }
            if (w->lewy->kolor == BLACK && w->prawy->kolor == BLACK) {
                w->kolor = RED;
                x = x->p;
            }
            else {
                if (w->prawy->kolor == BLACK) {
                    w->lewy->kolor = BLACK;
                    w->kolor = RED;
                    rotacja_w_prawo(w);
                    w = x->p->prawy;
                }
                w->kolor = x->p->kolor;
                w->p->kolor = BLACK;
                w->prawy->kolor = BLACK;
                rotacja_w_lewo(w);
                x = root;
            }
        }
        else {
            pnode w = x->p->lewy;
            if (w->kolor == RED) {
                w->kolor = BLACK;
                x->p->kolor = RED;
                rotacja_w_prawo(x->p);
                w = x->p->lewy;
            }
            if (w->prawy->kolor == BLACK && w->prawy->kolor == BLACK) {
                w->kolor = RED;
                x = x->p;
            }
            else {
                if (w->lewy->kolor == BLACK) {
                    w->prawy->kolor = BLACK;
                    w->kolor = RED;
                    rotacja_w_lewo(w);
                    w = x->p->lewy;
                }
                w->kolor = x->p->kolor;
                w->p->kolor = BLACK;
                w->lewy->kolor = BLACK;
                rotacja_w_prawo(w);
                x = root;
            }
        }
    }
    x->kolor = BLACK;
}

void delete(pnode z) {
    pnode x;
    pnode y = z;
    int y_original_kolor = y->kolor;
    if (z->lewy == NIL) {
        x = z->prawy;
        przeszczep(z, z->prawy);
    }
    else if (z->prawy == NIL) {
        x = z->lewy;
        przeszczep(z, z->lewy);
    }
    else {
        y = minimum(z->prawy);
        y_original_kolor = y->kolor;
        x = y->prawy;
        if (y != z->prawy) {
            przeszczep(y, y->prawy);
            y->prawy = z->prawy;
            y->prawy->p = y;
        }
        else x->p = y;
        przeszczep(z, y);
        y->lewy = z->lewy;
        y->lewy->p = y;
        y->kolor = z->kolor;
    }
    if (y_original_kolor == BLACK)
        napraw_delete(x);
    free(z);
}

pnode find(pnode v, int klu) {
    if (v == NIL) return NIL;
    if (v->klucz == klu) return v;
    if (klu < v->klucz)
        return find(v->lewy, klu);
    else return find(v->prawy, klu);
}

int main () {

    init();

    while (1) {
        int op, klu;
        scanf("%d %d", &op, &klu);
        if (op == 1) {
            insert(root, klu);
        }
        else {
            pnode v = find(root, klu);
            if (v != NIL)
                delete(v);
        }
        info();
    }

    return 0;
}