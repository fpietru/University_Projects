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
	for (int i=0; i<size(*h)/2; i++) {
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

// TODO: FIX IT
void merge(list *h, list *l2) {
	list h2 = NULL, p = NULL;
	while (*h != NULL && *l2 != NULL) {
		if ((*h)->wart <= (*l2)->wart) {
			printf("%d, h\n", (*h)->wart);
			if (h2 == NULL) {
				h2 = *h;
				p = *h;
			}
			p->next = *h;
			p = *h;
			(*h) = (*h)->next;
		}
		else {
			printf("%d, l2\n", (*l2)->wart);
			if (h2 == NULL) {
				 h2 = *l2;
				 p = *l2;
			}
			p->next = *l2;
			p = *l2;
			(*l2) = (*l2)->next;
		}
	}
	while (*h != NULL) {
		if (h2 == NULL) {
			h2 = *h;
			p = *h;
		}
		p->next = *h;
		p = *h;
		(*h) = (*h)->next;
	}
	while (*l2 != NULL) {
		if (h2 == NULL) {
			 h2 = *l2;
			 p = *l2;
		}
		p->next = *l2;
		p = *l2;
		(*l2) = (*l2)->next;
	}
	*h = h2;
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
	
	merge(&head, &l2);
	
	print(head);
	print(l2);
	
	
	
	return 0;
}
