#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int wart;
	struct node *next;
} node, *pnode;

void push(pnode *h, int a) {
	pnode u;
	u = malloc(sizeof(node));
	u->wart = a;
	u->next = *h;
	*h = u;
}

void print(pnode h) {
	while (h != NULL) {
		printf("%d ", h->wart);
		h = h->next;
	}
	printf("\n");
}

int size(pnode h) {
	int res = 0;
	while (h != NULL) {
		res++;
		h = h->next;
	}
	return res;
}

void split(pnode *h, pnode *h2) {
	pnode pocz = *h;
	int sz = size(*h);
	for (int i=1; i<sz/2; i++)
		(*h) = (*h)->next;
	
	(*h2) = (*h)->next;
	(*h)->next = NULL;
	(*h) = pocz;
}

void przeszczep(pnode *n1, pnode *n2) {
	pnode pom = *n1;
	(*n1) = (*n1)->next;
	pom->next = *n2;
	(*n2) = pom;
}

pnode merge(pnode h, pnode l2) {
	node res_pocz;
	pnode res = &res_pocz;
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

void MergeSort(pnode *h) {
	if (size(*h) == 1) return;
	pnode h2 = NULL;
	split(h, &h2);
	MergeSort(h);
	MergeSort(&h2);
	(*h) = merge(*h, h2);
}

int main () {
	pnode head = NULL;
	
	push(&head, 5);
	push(&head, 1);
	push(&head, 6);
	push(&head, 1);

	print(head);
	MergeSort(&head);
	print(head);
	
	return 0;
}
