/*
    Autor: Franciszek Pietrusiak
    Program do zabawy z biblioteką
    W nieskończonej pętli udostępnia dwie operacja:
        [1] - dodaj node'a o danym kluczu do drzewa
        [2] - usun node'a o danym kluczu z drzewa
        [3] - sprawdź, czy istnieje w drzewie node z danym kluczem
    Po każdej operacji wyświetlana jest struktura drzewa w formacie [klucz, kolor]

    Kompilacja:
    gcc -o main rb_tree.c main.c
*/
#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"

int main () {

    pnode root = init();

    while (1) {
        int op, klu;
        scanf("%d %d", &op, &klu);
        if (op == 1) {
            insert(&root, klu);
        }
        else if (op == 2) {
            pnode v = find(root, klu);
            if (v != NIL)
                deletenode(&root, v);
        }
        else if (op == 3) {
            pnode v = find(root, klu);
            if (v == NIL)
                printf("NIE\n");
            else printf("TAK\n");
        }
        info(root);
    }

    return 0;
}