#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//STACK - last in first out - lista simpla
struct Fotografie {
	int id;
	char* oras;
	float rezolutie;
};

typedef struct Fotografie Fotografie;
//typedef struct Node Node;
//
//struct Node {
//	Fotografie info;
//	Node* next;
//};
//
Fotografie citireFotografieFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	Fotografie f;
	fgets(buffer, 100, file);
	aux = strtok(buffer, sep);
	f.id = atoi(aux);
	aux = strtok(NULL, sep);
	f.oras = (char*)malloc(strlen(aux) + 1);
	strcpy(f.oras, aux);
	aux = strtok(NULL, sep);
	f.rezolutie = atof(aux);
	return f;
}

void afiseazaFoto(Fotografie f) {
	printf("Id: %d\n", f.id);
	printf("Oras: %s\n", f.oras);
	printf("Rezolutie: %.2f\n\n", f.rezolutie);
}

//void pushStack(Node** stack, Fotografie f) {
//	Node* nou = (Node*)malloc(sizeof(Node));
//	nou->info.id = f.id;
//	nou->info.rezolutie = f.rezolutie;
//	nou->info.oras = (char*)malloc(strlen(f.oras) + 1);
//	strcpy(nou->info.oras, f.oras);
//	nou->next = (*stack);
//	(*stack) = nou;
//}

//Fotografie popStack(Node** stack) {
//	Fotografie f;
//	if (*stack) {
//		Node* aux = (*stack);
//		(*stack) = aux->next;
//		aux->next = NULL;
//		f = aux->info;
//		free(aux);
//	}
//	return f;
//}
//
//Node* citireStackDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	Node* stack = NULL;
//	while (!feof(file)) {
//		Fotografie f = citireFotografieFisier(file);
//		pushStack(&stack, f);
//	}
//	fclose(file);
//	return stack;
//}
//
//void afiseazaStack(Node* stack) {
//	if (stack != NULL) {
//		Node* aux = stack;
//		while (aux != NULL) {
//			afiseazaFoto(aux->info);
//			aux = aux->next;
//		}
//	
//	}
//}
//
//void dezalocareStack(Node** stack) {
//	while ((*stack) != NULL) {
//		Fotografie f = popStack(stack);
//		free(f.oras);
//	}
//	
//}
//
//int sizeStack(Node* stack) {
//	int size = 0;
//	while (stack->next != NULL) {
//		size++;
//	}
//	return size;
//}

//QUEUE - coada, first in firt out 
typedef struct Node Node;
struct Node {
	Fotografie info;
	Node* next;
};

void enqueue(Node** queue,Fotografie f) {
	Node* nou = (Node*)malloc(sizeof(Node));
	nou->next = NULL;
	nou->info.id = f.id;
	nou->info.oras = (char*)malloc(strlen(f.oras) + 1);
	strcpy(nou->info.oras, f.oras);
	nou->info.rezolutie = f.rezolutie;
	if (*queue) {
		Node* aux = (*queue);
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		(*queue) = nou;
	}

}

Fotografie dequeue(Node** queue) {
	Fotografie f;
	if ((*queue)) {
		Node* aux = (*queue);
		f = aux->info;
		(*queue) = aux->next;
		aux->next = NULL;
		aux->info.oras = NULL;
		free(aux->info.oras);
		free(aux);
	}
	return f;
}


Node* citireQueueDinFisie(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Node* queue = NULL;
	while (!feof(file)) {
		Fotografie f = citireFotografieFisier(file);
		enqueue(&queue, f);
	}
	fclose(file);
	return queue;
}

void afiseazaQueue(Node* queue) {
	if(queue) {
		Node* aux = queue;
		while (aux != NULL) {
			afiseazaFoto(aux->info);
			aux = aux->next;
		}
	}
}

void dezalocareQueue(Node** queue) {
	Node* aux = (*queue);
	while (aux) {

	}
}

int main() {
	//Node* stack = citireStackDinFisier("fotografii.txt");
	//afiseazaStack(stack);
	//dezalocareStack(&stack);

	Node* queue = citireQueueDinFisie("fotografii.txt");
	afiseazaQueue(queue);
	afiseazaFoto(dequeue(&queue));
	dezalocareQueue(&queue);
	afiseazaQueue(queue);

	return 0;
}