/*
    Autor: Franciszek Pietrusiak
    Korzystałem z https://dl.ebooksworld.ir/books/Introduction.to.Algorithms.4th.Leiserson.Stein.Rivest.Cormen.MIT.Press.9780262046305.EBooksWorld.ir.pdf
    w szczególności opisane są tam Przypadki 1-3 i Przypadki 1-4 odpowiednio w napraw_insert() i napraw_deletenode()
    
    Drzewo Czerwono-Czarne musi spełniać warunki:
    -[1] Każdy node jest czerwony lub czarny
    -[2] Korzeń jest czarny
    -[3] Każdy liść jest czarny
    -[4] Jeśli node jest czerwony, to obaj jego synowie są czarni
    -[5] Dla każdego node'a wszystkie ścieżki wychodzące z niego do liści w jego poddrzewie zawierają tyle samo czarnych wierzchołków
*/
#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"

pnode NIL = NULL;

pnode init() {
    if (NIL == NULL) {
        NIL = (pnode)malloc(sizeof(node)); // NIL jest strażnikiem, który przypomina NULL'a, ale jego kolor jest zawsze czarny
        NIL->kolor = BLACK;
        NIL->klucz = 0;
        NIL->lewy = NULL;
        NIL->prawy = NULL;
        NIL->p = NULL;
    }
    return NIL; // korzeniem każdego pustego drzewa jest NIL
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

void info(pnode root) {
    print(root, 0);
    printf("\n");
}

void rotacja_w_lewo(pnode *root, pnode v) {
    pnode y = v->prawy;
    v->prawy = y->lewy; // przeszczep lewego syna y-ka jako prawego syna v
    if (y->lewy != NIL) // i jeśli on istnieje ...
        y->lewy->p = v; // ... to mu to powiedz
    y->p = v->p; // ojcem y-ka jest ojciec v
    if (v->p == NIL) // jeśli v był korzeniem ...
        *root = y; // ... y jest korzeniem
    else if (v == v->p->lewy) // jeśli v był lewym synem swojego ojca ...
        v->p->lewy = y; // ... to teraz y nim jest
    else v->p->prawy = y; // jeśli v był prawym synem swojego ojca, to analogicznie
    y->lewy = v; // v staje się lewym synem y-ka
    v->p = y; // ... i mu o tym mówimy
}

void rotacja_w_prawo(pnode *root, pnode v) {
    pnode y = v->lewy;
    v->lewy = y->prawy; // przeszczep prawego syna y-ka jako lewego syna v
    if (y->prawy != NIL) // i jeśli on istnieje ...
        y->prawy->p = v; // ... to mu to powiedz
    y->p = v->p;
    if (v->p == NIL)
        *root = y;
    else if (v == v->p->lewy)
        v->p->lewy = y;
    else v->p->prawy = y;
    y->prawy = v;
    v->p = y;
}

void napraw_insert(pnode *root, pnode v) {
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
                    rotacja_w_lewo(root, v);
                } // Przypadek 3
                v->p->kolor = BLACK;
                v->p->p->kolor = RED;
                rotacja_w_prawo(root, v->p->p);
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
                    rotacja_w_prawo(root, v);
                }
                v->p->kolor = BLACK;
                v->p->p->kolor = RED;
                rotacja_w_lewo(root, v->p->p);
            }            
        }
    }
    (*root)->kolor = BLACK; // upewnienie się, że warunek [2] jest spełniony
}

void insert(pnode *root, int klu) {
    pnode v = *root;
    pnode y = NIL;
    while (v != NIL) {  // schodzimy v aż do NIL'a
        y = v;
        if (klu < v->klucz)
            v = v->lewy;
        else v = v->prawy;
    }
    pnode u = newnode(klu, RED);
    u->p = y; // ojcem u jest y
    if (y == NIL) // jeśli drzewo jest puste
        *root = u;
    else if (u->klucz < y->klucz) // inaczej ustaw u jako właściwego syna y
        y->lewy = u;
    else y->prawy = u;
    napraw_insert(root, u); // napraw drzewo
}

void przeszczep(pnode *root, pnode v, pnode u) {
    if (v->p == NIL) // jeśli v jest korzeniem
        *root = u;
    else if (v == v->p->lewy) // inaczej podmień v przez u dla ojca v
        v->p->lewy = u;
    else v->p->prawy = u;
    u->p = v->p; // i powiedz u, że zmienił mu się ojciec
}

pnode minimum(pnode v) {
    while (v->lewy != NIL) // idź do lewego syna dopóki się da
        v = v->lewy;
    return v;
}

void napraw_deletenode(pnode *root, pnode v) {
    while (v != *root && v->kolor == BLACK) {
        if (v == v->p->lewy) { // jeśli v jest lewym synem
            pnode w = v->p->prawy; // w jest prawym bratem v
            if (w->kolor == RED) { // Przypadek 1
                w->kolor = BLACK;
                v->p->kolor = RED;
                rotacja_w_lewo(root, v->p);
                w = v->p->prawy;
            }
            if (w->lewy->kolor == BLACK && w->prawy->kolor == BLACK) { // Przypadek 2
                w->kolor = RED;
                v = v->p;
            }
            else {
                if (w->prawy->kolor == BLACK) { // Przypadek 3
                    w->lewy->kolor = BLACK;
                    w->kolor = RED;
                    rotacja_w_prawo(root, w);
                    w = v->p->prawy;
                } // Przypadek 4
                w->kolor = v->p->kolor;
                w->p->kolor = BLACK;
                w->prawy->kolor = BLACK;
                rotacja_w_lewo(root, w);
                v = *root;
            }
        }
        else { // symetryczna sytuacja
            pnode w = v->p->lewy;
            if (w->kolor == RED) {
                w->kolor = BLACK;
                v->p->kolor = RED;
                rotacja_w_prawo(root, v->p);
                w = v->p->lewy;
            }
            if (w->prawy->kolor == BLACK && w->prawy->kolor == BLACK) {
                w->kolor = RED;
                v = v->p;
            }
            else {
                if (w->lewy->kolor == BLACK) {
                    w->prawy->kolor = BLACK;
                    w->kolor = RED;
                    rotacja_w_lewo(root, w);
                    w = v->p->lewy;
                }
                w->kolor = v->p->kolor;
                w->p->kolor = BLACK;
                w->lewy->kolor = BLACK;
                rotacja_w_prawo(root, w);
                v = *root;
            }
        }
    }
    v->kolor = BLACK;
}

void deletenode(pnode *root, pnode v) {
    pnode x;
    pnode y = v;
    int y_original_kolor = y->kolor; // y może zmienić kolor, dlatego trzeba zapiamiętać jego początkowy kolor
    if (v->lewy == NIL) { // jak v nie ma lewego syna
        x = v->prawy;
        przeszczep(root, v, v->prawy); // to zastąp v przez jego prawego syna (może być NIL)
    }
    else if (v->prawy == NIL) { // symetrycznie gdy v nie ma prawego syna
        x = v->lewy;
        przeszczep(root, v, v->lewy);
    }
    else { // jeśli v ma obu synów
        y = minimum(v->prawy); // y zastąpi v
        y_original_kolor = y->kolor;
        x = y->prawy;
        if (y != v->prawy) { // jeśli y nie jest korzeniem poddrzewa v->prawy
            przeszczep(root, y, y->prawy); // >
            y->prawy = v->prawy;           // | zastępuję y przez jego prawego syna (wiadomo, że y nie ma lewego syna)
            y->prawy->p = y;               // >
        }
        else x->p = y; // jeśli jest korzeniem poddrzewa v->prawy
        przeszczep(root, v, y); // >
        y->lewy = v->lewy;      // | zastępuję v przez y
        y->lewy->p = y;         // |
        y->kolor = v->kolor;    // >
    }
    // tylko jeśli albo v był czarny i go usunęliśmy (gdy v nie ma jednego syna)
    // lub y był czarny, ale zastąpił v (gdy v ma obu synów)
    // to może dojść do naruszenia [5] warunku
    if (y_original_kolor == BLACK)
        napraw_deletenode(root, x);
    free(v); // zwolnij pamięć
}

pnode find(pnode v, int klu) {
    if (v == NIL) return NIL;
    if (v->klucz == klu) return v; // znalazłem node'a
    if (klu < v->klucz) // pojdź do jednego z synów
        return find(v->lewy, klu);
    else return find(v->prawy, klu);
}