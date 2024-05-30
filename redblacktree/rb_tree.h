/*
    Autor: Franciszek Pietrusiak
*/
#ifndef RB_TREE
#define RB_TREE

// kolory node'ów
#define RED 1
#define BLACK 0

// struktura node'a
typedef struct node {
    int klucz;
    int kolor;
    struct node *lewy, *prawy, *p; // p - wskaźnik do ojca
} node, *pnode;

// NIL jest odpowiednikiem NULL'a, ułatwia implementacje drzewa
extern pnode NIL;

// inicjalizacja drzewa RB, zwraca wskaźnik do korzenia
pnode init();

// tworzy nowy node, izolowany, o kluczu = klu i kolorze = kol
pnode newnode(int klu, int kol);

// rekurencyjnie wypisuje strukturę drzewa ukorzenionego w v (lvl=0)
void print(pnode v, int lvl);

// wypisuje podstawowe informacje o drzewie ukorzenionym w root
void info(pnode root);

// wykonuje rotacje w lewo względem v, w drzewie ukorzenionym w root
void rotacja_w_lewo(pnode *root, pnode v);

// wykonuje rotacje w prawo względem v, w drzewie ukorzenionym w root
void rotacja_w_prawo(pnode *root, pnode v);

// naprawia własności drzewa RB po wykonaniu funkcji insert zaczynając od v, w drzewie ukorzenionym w root
void napraw_insert(pnode *root, pnode v);

// dodaje do drzewa ukorzenionego w root node'a o kluczu = klu
void insert(pnode *root, int klu);

// zastępuje poddrzewo v przez poddrzewo u, w drzewie ukorzenionym w root
void przeszczep(pnode *root, pnode v, pnode u);

// zwraca wskaźnik do node'a, którego klucz jest minimalny, w drzewie ukorzenionym w v
pnode minimum(pnode v);

// naprawia własności drzewa RB po wykonaniu funkcji deletenode zaczynając od v, w drzewie ukorzenionym w root
void napraw_deletenode(pnode *root, pnode v);

// usuwa z drzewa ukorzenionego w root node'a wskazywanego przez v
void deletenode(pnode *root, pnode v);

// zwraca wskaźnik do node'a o kluczu = klu, w drzewie ukorzenionym w v 
pnode find(pnode v, int klu);

#endif // RB_TREE