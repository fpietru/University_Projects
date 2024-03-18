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

void split(list *h, list *l2) {
	list pocz = *h;
	int n = size(*h);
	for (int i=(!(n&1)); i<n/2; i++) {
		*h = (*h)->next;
	}
	*l2 = (*h)->next;
	(*h)->next = NULL;
	*h = pocz;
}

void reverse(list *h) {
	list h2 = NULL, p = NULL;
	while (*h != NULL) {
		p = (*h)->next;
		(*h)->next = h2;
		h2 = *h;
		*h = p;
	}
	*h = h2;
}

void przeszczep(list *n1, list *n2) {
	list pom = *n1;
	(*n1) = pom->next;
	pom->next = *n2;
	(*n2) = pom;
}

list merge(list h, list l2) {
	Node res_pocz;
	list res = &res_pocz;
	res->next = NULL;
	while (1) {
		if (h == NULL) {
			res->next = l2;
			break;
		}
		else if (l2 == NULL) {
			res->next = h;
			break;
		}
		if (h->wart <= l2->wart) przeszczep(&h, &(res->next));
		else przeszczep(&l2, &(res->next));
		res = res->next;
	}
	return (res_pocz.next);
}

int main () {
	list head = NULL;
	list l2 = NULL;
	
	push(&head, 5);
	push(&head, 4);
	push(&head, 3);
	push(&head, 2);
	push(&head, 1);
	
	push(&l2, 5);
	push(&l2, 5);
	push(&l2, 4);
	push(&l2, 4);
	push(&l2, 3);
	
	
	print(head);
	print(l2);
	
	list merged = merge(head, l2);
	
	print(merged);
	print(head);
	print(l2);
	
	
	
	return 0;
}
