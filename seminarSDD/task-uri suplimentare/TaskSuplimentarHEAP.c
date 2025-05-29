//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
////HEAPUL NU TREBUIE SA FIE SORTAT LA AFISARE DW
////heap - coada de prioritati
////min heap - cele mai mici sus
////max heap - cele mai mari sus
//
//struct Pacient {
//	char* nume;
//	int varsta;
//	int grad;
//};
//
//typedef struct Pacient Pacient;
//typedef struct Heap Heap;
//
//struct Heap {
//	Pacient* vector;
//	int lungime;
//	int nrElemente;
//};
//
//Pacient citirePacientDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	Pacient p;
//	char* aux;
//	aux = strtok(buffer, sep);
//	p.nume = (char*)malloc(strlen(aux) + 1);
//	strcpy(p.nume, aux);
//	aux = strtok(NULL, sep);
//	p.varsta = atoi(aux);
//	aux = strtok(NULL, sep);
//	p.grad = atoi(aux);
//	return p;
//}
//
//void afiseazaPacient(Pacient p) {
//	printf("Numele pacientului: %s \n", p.nume);
//	printf("Varsta: %d \n", p.varsta);
//	printf("Grad: %d \n\n", p.grad);
//}
//
//Heap initializareHeap(int lungime) {
//	Heap heap;
//	heap.lungime = lungime;
//	heap.nrElemente = 0;
//	heap.vector = (Pacient*)malloc(sizeof(Pacient) * lungime);
//	return heap;
//}
//
//void filtrareMinHeap(Heap heap, int poz) {
//	int fiuS = poz * 2 + 1;
//	int fiuD = poz * 2 + 2;
//	int min = poz;
//	if (fiuS < heap.nrElemente && heap.vector[fiuS].grad < heap.vector[poz].grad) {
//		min = fiuS;
//	}
//	if (fiuD < heap.nrElemente && heap.vector[fiuD].grad < heap.vector[poz].grad) {
//		min = fiuD;
//	}
//	if (min != poz) {
//		Pacient aux = heap.vector[min];
//		heap.vector[min] = heap.vector[poz];
//		heap.vector[poz] = aux;
//		//acum verificam daca mai trebuie sa sortam
//		if (min <= (heap.nrElemente - 2) / 2){
//			filtrareMinHeap(heap, min);
//		}
//	}
//}
//
//Heap citireHeapDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	Heap heap = initializareHeap(11);
//	while (!feof(file)) {
//		heap.vector[heap.nrElemente++] = citirePacientDinFisier(file);
//	}
//	fclose(file);
//	for (int i = (heap.nrElemente - 2) / 2; i >= 0; i--) {
//		filtrareMinHeap(heap, i);
//	}
//	return heap;
//}
//
//
//void afisareHeap(Heap heap) {
//	for (int i = 0; i < heap.nrElemente; i++) {
//		afiseazaPacient(heap.vector[i]);
//	}
//}
//
//void dezalocareHeap(Heap* heap) {
//	for (int i = 0; i < heap->nrElemente; i++) {
//		free(heap->vector[i].nume);
//	}
//	free(heap->vector);
//	heap->vector = NULL;
//	heap->lungime = 0;
//	heap->nrElemente = 0;
//}
//
//Pacient extragePacientiDinHeap(Heap* heap) {
//	if (heap->vector != 0) {
//		Pacient aux = heap->vector[0];
//		heap->vector[0] = heap->vector[heap->nrElemente - 1];
//		heap->vector[heap->nrElemente - 1] = aux;
//		heap->nrElemente--;
//		for (int i = (heap->nrElemente - 2) / 2; i >= 0; i--) {
//			filtrareMinHeap(*heap, i);
//		}
//		return aux;
//	}
//}
//
//int main() {
//	Heap minHeap = citireHeapDinFisier("pacienti.txt");
//	afisareHeap(minHeap);
//
//	printf("\n----Extragere pacienti: -----\n");
//	afiseazaPacient(extragePacientiDinHeap(&minHeap));
//	printf("\n----Verificare extragere: -----\n");
//	afisareHeap(minHeap);
//
//	dezalocareHeap(&minHeap);
//	return 0;
//}
