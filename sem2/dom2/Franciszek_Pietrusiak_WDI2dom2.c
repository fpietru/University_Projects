/*
    Franciszek Pietrusiak 458987
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int wart;
	struct Node *next;
} Node, *list;

void push(list *h, int a) {
    list u = malloc(sizeof(Node));
    u->wart = a;
    u->next = *h;
    *h = u;
}

void print(list h) {
    while (h != NULL) {
        printf("%d ", h->wart);
        h = h->next;
    }
	printf("\n");
}

/*
	Funkcja split dzieląca listę *h na dwie odzielne listy: l1, l2
	, gdzie l1 zawiera nody z wartościami <= k,
	a l2 zawiera nody z wartosciami > k
	
	Funkcja sprawia, że lista *h staje się listą l1, oraz zwraca l2

	Schemat działania:
	Idę po wszystkich nodach z listy *h, i
	-> jeśli (*h)->wart <= k to podpinam ten node do ostatniego node'a z listy l1
	-> jeśli (*h)->wart > k to podpinam ten node do ostatniego node'a z listy l2
	dla list l1, l2 zapamiętuję ich początek i koniec
*/
list split(list *h, int k) {
    list l1_kon = NULL, l2_kon = NULL;
	list l1_pocz = NULL, l2_pocz = NULL;
    while (*h != NULL) {
		if ((*h)->wart <= k) {
			if (l1_kon == NULL) {
				l1_kon = *h;
				l1_pocz = l1_kon;
			}
			else {
				l1_kon->next = *h;
				l1_kon = *h;
			}
		}
		else {
			if (l2_kon == NULL) {
				l2_kon = *h;
				l2_pocz = l2_kon;
			}
			else {
				l2_kon->next = *h;
				l2_kon = *h;
			}
		}
		(*h) = (*h)->next;
		// dlatego, że mogę już nie natrafić na następny node do podpięcia na koniec listy
		if (l1_kon != NULL) l1_kon->next = NULL;
		if (l2_kon != NULL) l2_kon->next = NULL;
    }
	(*h) = l1_pocz;
	return l2_pocz;
}

int main () {
    FILE *fin = fopen("./dane.txt", "r");

    list lista = NULL;

    int klucz;
    fscanf(fin, "%d", &klucz); 
    
    int elem;
    while (fscanf(fin, "%d", &elem) != EOF) {
        push(&lista, elem);
    }
    print(lista);
	
	list lista2 = split(&lista, klucz);

	print(lista);
	print(lista2);

    fclose(fin);
    return 0;
}