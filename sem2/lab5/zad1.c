/*
    Zadanie: Napisać funkcję, która usuwa wszystkie powtórzenia z posortowanej listy
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int wart;
	struct Node *next;
} Node, *list;

void push(list *h, int a) {
	list u;
	u = malloc(sizeof(Node));
	u->wart = a;
	u->next = *h;
	*h = u;
}

void pop(list *h) {
	list u;
	if (*h != NULL) {
		u = *h;
		*h = (*h)->next;
		free(u);
	}
}

void print(list h) {
	while (h != NULL) {
		printf("%d ", h->wart);
		h = h->next;
	}
	printf("\n");
}

void wczytaj(list *h) {
	int a;
	while (scanf("%d", &a) > 0)
		push(h, a);
}

void usunpowtorzenia(list h) {
	list pom;
    while (h != NULL) {
        while (h->next != NULL && h->wart == (h->next)->wart) {
            pom = h->next;
            h->next = (h->next)->next;
            free(pom);
        }
        h = h->next;
    }
}

int main () {
	list head = NULL;
	
	wczytaj(&head);
    print(head);
    usunpowtorzenia(head);
    print(head);
	
	return 0;
}
