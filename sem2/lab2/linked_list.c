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

list find(list h, int a) {
	while ((h!=NULL) && (h->wart!=a))
		h = h->next;
	return h;
}

int size(list h) {
	int res = 0;
	while (h != NULL) {
		res++;
		h = h->next;
	}
	return res;
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

void zpliku(list *h) {
	FILE *fin = fopen("dane.txt", "r");
	int a;
	while (fscanf(fin, "%d", &a) != EOF)
		push(h, a);
	fclose(fin);
}

// TODO: nie zmieniac h przy splitcie
void split(list h, list *l1, list *l2) {
	list pocz = h;
	*l1 = h;
	for (int i=0; i<size(h)/2; i++) {
		(*l1) = (*l1)->next;
		h = h->next;
	}
	*l2 = h->next;
	(*l1)->next = NULL;
	*l1 = pocz;
}

int main () {
	list head = NULL;
	
	// wczytaj(&head);
	zpliku(&head);
	
	print(head);
	
	printf("%d\n", size(head));
	
	list l1 = NULL;
	list l2 = NULL;
	split(head, &l1, &l2);
	print(l1);
	print(l2);
	
	printf("%d %d %d\n", size(head), size(l1), size(l2));
	
	print(head);
	
	return 0;
}
