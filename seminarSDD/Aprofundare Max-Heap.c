//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct Persoana {
//	int id;
//	char* nume;
//	unsigned char serie;
//	int nr;
//	float* note;
//};
//
//typedef struct Persoana Persoana;
//typedef struct MHeap MHeap;
//
//struct MHeap {
//	int lungime;
//	int elemente;
//	Persoana* vector;
//};
//
//Persoana citestePersoanaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Persoana p;
//	aux = strtok(buffer, sep);
//	p.id = atoi(aux);
//	aux = strtok(NULL, sep);
//	p.nume = (char*)malloc(strlen(aux) + 1);
//	strcpy(p.nume, aux);
//	p.serie = *strtok(NULL, sep);
//	aux = strtok(NULL, sep);
//	p.nr = atoi(aux);
//	p.note = NULL;
//	if (p.nr != 0) {
//		p.note = (float*)malloc(sizeof(float) * p.nr);
//		for (int i = 0; i < p.nr; i++) {
//			aux = strtok(NULL, sep);
//			p.note[i] = atof(aux);
//		}
//	}
//	return p;
//}
//
//void afisarePersoana(Persoana p) {
//	printf("\n\nId: %d\n",p.id);
//	printf("Nume: %s\n",p.nume);
//	printf("Serie: %c\n",p.serie);
//	printf("Numar de note: %d\n", p.nr);
//	printf("Notele: \n");
//	for (int i = 0; i < p.nr; i++) {
//		printf("%.2f ", p.note[i]);
//	}
//}
//
//
//
//MHeap initializareMHeap(int lungime) {
//	MHeap heap;
//	heap.lungime = lungime;
//	heap.elemente = 0;
//	heap.vector = (Persoana*)malloc(sizeof(Persoana) * lungime);
//	return heap;
//}
//
//void filtreazaHeap(MHeap heap,int poz) {
//	int fiuS = 2 * poz - 1;
//	int fiuD = 2 * poz - 2;
//	int max = poz;
//	if (fiuS<heap.elemente && heap.vector[fiuS].id>heap.vector[poz].id) {
//		max = fiuS;
//	}
//	if (fiuD<heap.elemente && heap.vector[fiuD].id>heap.vector[poz].id) {
//		max = fiuD;
//	}
//
//	if (poz != max) {
//		Persoana aux = heap.vector[max];
//		heap.vector[max] = heap.vector[poz];
//		heap.vector[poz] = aux;
//		if (max <= ((heap.elemente + 2) / 2)) {
//			filtreazaHeap(heap, poz);
//		}
//	}
//}
//
//MHeap citireMHeapDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	MHeap heap = initializareMHeap(6);
//	while (!feof(file)) {
//		heap.vector[heap.elemente++] = citestePersoanaDinFisier(file);
//	}
//	fclose(file);
//	for (int i = (heap.elemente - 2) / 2; i >= 0; i--) {
//		filtreazaHeap(heap, i);
//	}
//	return heap;
//}
//
//void afiseazaHeap(MHeap heap) {
//	for (int i = 0; i < heap.elemente; i++) {
//		afisarePersoana(heap.vector[i]);
//	}
//}
//
//void dezalocareHeap(MHeap* heap) {
//	for (int i = 0; i < heap->lungime; i++) {
//		free(heap->vector[i].nume);
//		free(heap->vector[i].note);
//	}
//	free(heap->vector);
//	heap->vector = NULL;
//	heap->elemente = 0;
//	heap->lungime = 0;
//}
//
//Persoana extragerePersoanaDinHeap(MHeap* heap) {
//	if (heap->elemente != 0) {
//		Persoana aux = heap->vector[0];
//		heap->vector[0] = heap->vector[heap->elemente-1];
//		heap->vector[heap->elemente-1] = aux;
//		heap->elemente--;
//		//filtram iar parintii
//		for (int i = (heap->elemente - 2) / 2; i >= 0; i--) {
//			filtreazaHeap(*heap, i);
//		}
//		return aux;
//	}
//}
//
//
//int main() {
//	MHeap heap = citireMHeapDinFisier("persoane.txt");
//	afiseazaHeap(heap);
//	Persoana scos = extragerePersoanaDinHeap(&heap);
//	printf("\n-----------persoana extrasa-----------\n");
//	afisarePersoana(scos);
//	printf("\n-----------heap fara persoana extrasa-----------\n"); 
//	afiseazaHeap(heap);
//	
//	dezalocareHeap(&heap);
//	return 0;
//}