/*
Dwu-lista cykliczna to dwie listy cykliczne, tego samego rozmiaru,
których elementy są połączone wskaźnikami. Elementy list są powiązane
w przeciwnych kierunkach.
typedef struct elem {
    int val;
    elem *next, *other;
} elem;  
typedef elem* dwu_lista;
Dwu-listę mamy daną jako wskaźnik do jednego z elementów jednej z list
(nazywanej umownie ,,pierwszą'', a drugą z nich nazywamy umownie ,,drugą'').
Napisz funkcję void rotate(dwu_lista lst), która przesunie drugą
listę (względem pierwszej listy), zgodnie z kierunkiem jej wskaźników next. 
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct elem {
    int val;
    struct elem *next, *other;
} elem;
typedef elem *dwu_lista;

void rotate(dwu_lista l) {
    dwu_lista curr = l;
    do {
        dwu_lista next = curr->next;
        dwu_lista up = next->other->next;
        next->other = up;
        up->other = next;
        curr = next;
    } while (curr != l);
}

int main () {

    return 0;
}