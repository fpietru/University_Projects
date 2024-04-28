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

int pop(list *h) {
	if (*h != NULL) {
		list tmp = *h;
		(*h) = (*h)->next;
		free(tmp);
		return 1;
	}
	return 0;
}

void print(list h) {
	printf("[");
	while (h != NULL) {
		printf("%d", h->wart);
		if (h->next != NULL)
			printf(", ");
		h = h->next;
	}
	printf("]\n");
}

int main () {
	list stos = NULL;

	while (1) {
		printf("\e[1;1H\e[2J"); // do wyczyszczenia konsoli
		int operacja = -1;
		printf("---\n(1) dodaj element do stosu\n(2) usun element ze stosu\n(3) wypisz stos\n---\nOperacja: ");
		scanf("%d", &operacja);
		
		if (operacja == 1) {
			int el = -1;
			printf("element = ");
			scanf("%d", &el);
			push(&stos, el);
			printf("[dodano do stosu]\n");
		}
		else if (operacja == 2) {
			if (pop(&stos)) printf("[usunieto ze stosu]\n");
			else printf("[stos pusty]\n");
		}
		else if (operacja == 3) {
			printf("[zawartosc stosu]\n");
			print(stos);
		}
	
		printf("\n[nacisnij enter]\n");
		getchar(); // ten getchar() zjada enter z ostatniego scanf'a
		getchar();
	}

	return 0;
}
