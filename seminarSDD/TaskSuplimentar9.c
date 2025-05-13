#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//heap - coada de prioritati
//min heap - cele mai mici sus
//max heap - cele mai mari sus

struct Pacient {
	char* nume;
	int varsta;
	int grad;
};

typedef struct Pacient Pacient;

struct Heap {
	int lungime;
	Pacient* vector;
	int nrPacienti;
};
typedef struct Heap Heap;

Pacient citirePacientDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Pacient p;
	aux = strtok(buffer, sep);
	p.nume = (char*)malloc(strlen(aux) + 1);
	strcpy(p.nume, aux);
	aux = strtok(NULL, sep);
	p.varsta = atoi(aux);
	aux = strtok(NULL, sep);
	p.grad = atoi(aux);
	return p;
}

void afiseazaPacient(Pacient p) {
	printf("Numele: %s\n", p.nume);
	printf("Varsta: %d",p.varsta);
	printf("Grad: %d",p.grad);
}

Heap initializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.nrPacienti = 0;
	heap.vector = (Pacient*)malloc(sizeof(Pacient) * lungime);
	return heap;
}

//fiu = 2*poz+1 sau +2
//parinte = 

void filtrareHeap(Heap heap, int poz) {
	int pozFiuSt = 2 * poz + 1;
	int pozFiuDr = 2 * poz + 2;
	int pozMaxim = poz;
	if (heap.vector[pozMaxim].grad < heap.vector[pozFiuSt].grad) {
		pozMaxim = pozFiuSt;                   
	}
	if (heap.vector[pozMaxim].grad < heap.vector[pozFiuDr].grad) {
		pozMaxim = pozFiuDr;
	}
}