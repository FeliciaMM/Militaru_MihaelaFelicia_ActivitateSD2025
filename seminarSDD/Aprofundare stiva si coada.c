//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////STACK - last in first out - lista simpla
//struct Fotografie {
//	int id;
//	char* oras;
//	float rezolutie;
//};
//
//typedef struct Fotografie Fotografie;
////typedef struct Node Node;
////
////struct Node {
////	Fotografie info;
////	Node* next;
////};
////
//Fotografie citireFotografieFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	char* aux;
//	Fotografie f;
//	fgets(buffer, 100, file);
//	aux = strtok(buffer, sep);
//	f.id = atoi(aux);
//	aux = strtok(NULL, sep);
//	f.oras = (char*)malloc(strlen(aux) + 1);
//	strcpy(f.oras, aux);
//	aux = strtok(NULL, sep);
//	f.rezolutie = atof(aux);
//	return f;
//}
//
//void afiseazaFoto(Fotografie f) {
//	printf("Id: %d\n", f.id);
//	printf("Oras: %s\n", f.oras);
//	printf("Rezolutie: %.2f\n\n", f.rezolutie);
//}
//
////void pushStack(Node** stack, Fotografie f) {
////	Node* nou = (Node*)malloc(sizeof(Node));
////	nou->info.id = f.id;
////	nou->info.rezolutie = f.rezolutie;
////	nou->info.oras = (char*)malloc(strlen(f.oras) + 1);
////	strcpy(nou->info.oras, f.oras);
////	nou->next = (*stack);
////	(*stack) = nou;
////}
//
////Fotografie popStack(Node** stack) {
////	Fotografie f;
////	if (*stack) {
////		Node* aux = (*stack);
////		(*stack) = aux->next;
////		aux->next = NULL;
////		f = aux->info;
////		free(aux);
////	}
////	return f;
////}
////
////Node* citireStackDinFisier(const char* numeFisier) {
////	FILE* file = fopen(numeFisier, "r");
////	Node* stack = NULL;
////	while (!feof(file)) {
////		Fotografie f = citireFotografieFisier(file);
////		pushStack(&stack, f);
////	}
////	fclose(file);
////	return stack;
////}
////
////void afiseazaStack(Node* stack) {
////	if (stack != NULL) {
////		Node* aux = stack;
////		while (aux != NULL) {
////			afiseazaFoto(aux->info);
////			aux = aux->next;
////		}
////	
////	}
////}
////
////void dezalocareStack(Node** stack) {
////	while ((*stack) != NULL) {
////		Fotografie f = popStack(stack);
////		free(f.oras);
////	}
////	
////}
////
////int sizeStack(Node* stack) {
////	int size = 0;
////	while (stack->next != NULL) {
////		size++;
////	}
////	return size;
////}
//
////QUEUE - coada, first in firt out 
//typedef struct Node Node;
//struct Node {
//	Fotografie info;
//	Node* next;
//};
//
//void enqueue(Node** queue,Fotografie f) {
//	Node* nou = (Node*)malloc(sizeof(Node));
//	nou->next = NULL;
//	nou->info.id = f.id;
//	nou->info.oras = (char*)malloc(strlen(f.oras) + 1);
//	strcpy(nou->info.oras, f.oras);
//	nou->info.rezolutie = f.rezolutie;
//	if (*queue) {
//		Node* aux = (*queue);
//		while (aux->next != NULL) {
//			aux = aux->next;
//		}
//		aux->next = nou;
//	}
//	else {
//		(*queue) = nou;
//	}
//
//}
//
//Fotografie dequeue(Node** queue) {
//	Fotografie f;
//	if ((*queue)) {
//		Node* aux = (*queue);
//		f.id = aux->info.id;
//		f.rezolutie = aux->info.rezolutie;
//		f.oras = (char*)malloc(strlen(aux->info.oras) + 1);
//		strcpy(f.oras, aux->info.oras);
//		(*queue) = aux->next;
//		aux->next = NULL;
//		free(aux->info.oras);
//		free(aux);
//	}
//	return f;
//}
//
//
//Node* citireQueueDinFisie(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	Node* queue = NULL;
//	while (!feof(file)) {
//		Fotografie f = citireFotografieFisier(file);
//		enqueue(&queue, f);
//	}
//	fclose(file);
//	return queue;
//}
//
//void afiseazaQueue(Node* queue) {
//	if(queue) {
//		Node* aux = queue;
//		while (aux != NULL) {
//			afiseazaFoto(aux->info);
//			aux = aux->next;
//		}
//	}
//}
//
//void dezalocareQueue(Node** queue) {
//	while (*queue != NULL) {
//		Fotografie f = dequeue(queue);
//		free(f.oras);
//	}
//}
//
//void removeByIdQueue(Node** queue, int id) {
//	Node* tempQueue = NULL;
//	while (*queue != NULL) {
//		Fotografie f = dequeue(queue);
//		if (f.id != id) {
//			enqueue(&tempQueue, f); // păstrăm elementul
//		}
//		else {
//			free(f.oras); // eliminăm elementul
//		}
//	}
//	*queue = tempQueue; // înlocuim coada veche
//}
// 
// 
// Node* tempqueue =NULL;
// while(*queue !=NULL;
// Fotografie f = dequeue(queue);
// if(f.id !=id){
// enqueue(&tempqueue,f)}else{
// free(f.oras);
// }
// }
// *queue = tempQueue;
//
////void removeByIdStack(Node** stack, int id) {
////	Node* auxStack = NULL;
////	while (*stack != NULL) {
////		Fotografie f = popStack(stack);
////		if (f.id != id) {
////			pushStack(&auxStack, f); // păstrăm elementul
////		}
////		else {
////			free(f.oras); // eliminăm
////		}
////	}
////	// refacem stiva originală
////	while (auxStack != NULL) {
////		Fotografie f = popStack(&auxStack);
////		pushStack(stack, f);
////	}
////}
//
//float rezolutieTotalaQueue(Node* queue) {
//	float suma = 0.0f;
//	Node* aux = queue;
//	while (aux != NULL) {
//		suma += aux->info.rezolutie;
//		aux = aux->next;
//	}
//	return suma;
//}
//
//float rezolutieTotalaStack(Node* stack) {
//	float suma = 0.0f;
//	Node* aux = stack;
//	while (aux != NULL) {
//		suma += aux->info.rezolutie;
//		aux = aux->next;
//	}
//	return suma;
//}
//
//int main() {
//	//Node* stack = citireStackDinFisier("fotografii.txt");
//	//afiseazaStack(stack);
//	//dezalocareStack(&stack);
//
//	Node* queue = citireQueueDinFisie("fotografii.txt");
//	afiseazaQueue(queue);
//	afiseazaFoto(dequeue(&queue));
//	dezalocareQueue(&queue);
//	afiseazaQueue(queue);
//
//	return 0;
//}