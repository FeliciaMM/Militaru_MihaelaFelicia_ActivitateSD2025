//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
// 
// TO DO
//struct Persoana {
//	int id;
//	char* nume;
//	unsigned char serie;
//	int nrNote;
//	float* note;
//};
//
////STACK - STIVA
//typedef struct Persoana Persoana;
//typedef struct Node Node;
//
//struct Node {
//	Persoana info;
//	Node* next;
//};
//
//Persoana citirePersoanaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	Persoana p;
//	char* aux;
//	fgets(buffer, 100, file);
//	aux = strtok(buffer, sep);
//	p.id = atoi(aux);
//	aux = strtok(NULL, sep);
//	p.nume = (char*)malloc(strlen(aux) + 1);
//	strcpy(p.nume, aux);
//	p.serie = *strtok(NULL, sep);
//	aux = strtok(NULL, sep);
//	p.nrNote = atoi(aux);
//	p.note = NULL;
//	if (p.nrNote > 0) {
//		p.note = (float*)malloc(sizeof(float) * p.nrNote);
//		for (int i = 0; i < p.nrNote; i++) {
//			aux = strtok(NULL, sep);
//			p.note[i] = atof(aux);
//		}
//	}
//	return p;
//}
//
//void afisarePersoana(Persoana p) {
//	printf("Id: %d\n",p.id);
//	printf("Nume: %s\n",p.nume);
//	printf("Serie: %c\n",p.serie);
//	printf("Numarul de note: %d\n",p.nrNote);
//	for (int i = 0; i < p.nrNote; i++) {
//		printf("%.2f ", p.note[i]);
//	}
//	printf("\n\n");
//}
//
//void pushStack(Node** stack, Persoana p) {
//	Node* nou = (Node*)malloc(sizeof(Node));
//	nou->info = p;
//	nou->next = (*stack);
//	(*stack) = nou;
//}
//
//Persoana popStack(Node** stack) {
//	Persoana p;
//	if (*stack) {
//		Node* aux = *stack;
//		p = aux->info;
//		(*stack) = aux->next;
//		aux->next = NULL;
//		free(aux);
//
//	}
//	return p;
//}
//
//Node* citireStackDinFisier(const char* numeFisier) {
//	Node* stack = NULL;
//	FILE* file = fopen(numeFisier, "r");
//	while (!feof(file)) {
//		Persoana p = citirePersoanaDinFisier(file);
//		pushStack(&stack, p);
//	}
//	fclose(file);
//	return stack;
//}
//
//void afisareStack(Node* stack) {
//	while (stack != NULL) {
//		afisarePersoana(stack->info);
//		stack = stack->next;
//	}
//}
//
////QUEUE - COADA
//typedef struct NodeDublu NodeDublu;
//
//typedef struct ListaDubla ListaDubla;
//
//struct NodeDublu {
//	Persoana info;
//	NodeDublu* next;
//	NodeDublu* prev;
//};
//
//struct ListaDubla {
//	NodeDublu* first;
//	NodeDublu* last;
//};
//
//void enqueue(ListaDubla* queue, Persoana p) {
//	NodeDublu* nou = (NodeDublu*)malloc(sizeof(NodeDublu));
//	nou->info = p;
//	nou->next = NULL;
//	nou->prev = queue->last;
//	if (queue->last != NULL) {
//		queue->last->next = nou;	
//	}
//	else {
//		queue->first = nou;
//	}
//	queue->last = nou;
//}
//
//Persoana dequeue(ListaDubla* queue) {
//	Persoana p;
//	if (queue->first != NULL) {
//		p = queue->first->info;
//		NodeDublu* aux = queue->first;
//		if (queue->first->next != NULL) {
//			queue->first = queue->first->next;
//			queue->first->prev = NULL;
//		}
//		else {
//			queue->first = NULL;
//			queue->last = NULL;
//		}
//		free(aux);
//	}
//	return p;
//
//}
//
//
//int main() {
//	Node* stack = citireStackDinFisier("persoane.txt");
//	afisareStack(stack);
//	popStack(&stack);
//	printf("STack dupa pop");
//	afisareStack(stack);
//	return 0;
//}
