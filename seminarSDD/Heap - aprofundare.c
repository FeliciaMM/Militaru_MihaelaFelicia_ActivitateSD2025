 //#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////un vector in care gasim elementele ordonate in functie de marime
////cele mai mici/mai mari sus in functie daca e min sau max
////ACESTA ESTE UN EXEMPLU DE MAX HEAP
//struct Avion {
//	char* nume;
//	int nrLocuri;
//	int locuriOcupate;
//	float* pretBilet;
//};
//
//typedef struct Avion Avion;
//
//
//struct Heap {
//	int lungime;//cate spatii sunt disponibile
//	int nrElemente;//cate spatii neascunse
//	Avion* vector;
//};
//
//typedef struct Heap Heap;
//
//Avion citireAvionDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Avion a;
//	aux = strtok(buffer, sep);
//	if (aux != NULL) {
//		a.nume = (char*)malloc(strlen(aux) + 1);
//		strcpy(a.nume, aux);
//	}
//	else {
//		a.nume = NULL;
//	}
//	aux = strtok(NULL, sep);
//	a.nrLocuri = atoi(aux);
//	aux = strtok(NULL, sep);
//	a.locuriOcupate = atoi(aux);
//	a.pretBilet = NULL;
//	if (a.locuriOcupate > 0) {
//		a.pretBilet = (float*)malloc(a.locuriOcupate * sizeof(float));
//		for (int i = 0; i < a.locuriOcupate; i++) {
//			aux = strtok(NULL, sep);
//			if (aux != NULL) {
//				a.pretBilet[i] = atof(aux);
//			}
//
//		}
//	}
//	return a;
//}
//
//void afisareAvion(Avion a) {
//	printf("\nNume: %s\n", a.nume);
//	printf("Nr locuri: %d\n", a.nrLocuri);
//	printf("Locuri ocupate: %d\n", a.locuriOcupate);
//	printf("Pretul biletelor: ");
//	for (int i = 0; i < a.locuriOcupate; i++) {
//		printf("%.2f \n", a.pretBilet[i]);
//	}
//}
//
//Heap initializare(int lungime) {
//	Heap heap;
//	heap.lungime = lungime;
//	heap.nrElemente = 0;
//	heap.vector = (Avion*)malloc(sizeof(Avion) * heap.lungime);
//	return heap;
//}
//
////primim pozitia nodului, folosind formulele fiuS = 2*poz+1 sau +2
//void filtrareHeap(Heap heap, int poz) {
//	int pozFius = 2 * poz + 1;
//	int pozFiud = 2 * poz + 2;
//	int pozMaxim = poz;
//	if (pozFius < heap.nrElemente && heap.vector[poz].nrLocuri < heap.vector[pozFius].nrLocuri) {
//		pozMaxim = pozFius;
//	}
//	if (pozFiud < heap.nrElemente && heap.vector[poz].nrLocuri < heap.vector[pozFiud].nrLocuri) {
//		pozMaxim = pozFiud;
//	}
//	if (pozMaxim != poz) {
//		Avion aux = heap.vector[pozMaxim];
//		heap.vector[pozMaxim] = heap.vector[poz];
//		heap.vector[poz] = aux;
//		if (pozMaxim <= (heap.nrElemente - 2)/2) {
//			filtrareHeap(heap,pozMaxim);
//		}
//	}
//}
//
//Heap citireAvioaneDinFiiser(char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	Heap heap = initializare(4);
//	if (file) {
//		while (!feof(file)) {
//			heap.vector[heap.nrElemente++] = citireAvionDinFisier(file);
//		}
//		fclose(file);
//	}
//	
//	//incepem de la ultimul nod si filtram
//	//apelam dupa ce le citim pentru ca dac filtram si citim concomitent ajungem la prea mutl einterschimbari
//	for (int i = (heap.nrElemente - 2) / 2; i >= 0; i--) {
//		filtrareHeap(heap, i);
//	}
//	return heap;
//}
//
//void afiseazaHeap(Heap heap) {
//	for (int i = 0; i < heap.nrElemente; i++) {
//		afisareAvion(heap.vector[i]);
//	}
//}
//
////verificam lungimea comparaiv cu nr de elemente
//void afiseazaHeapAscuns(Heap heap) {
//	//AICI ARE LOC UN BUG (TO DO)
//	for (int i = heap.nrElemente; i < heap.lungime; i++) {
//		afisareAvion(heap.vector[i]);
//		
//	}
//}
//
////vom intersecta numarul de sus cu ultimul de sus si il extragem
//// //ascundem nr extras si micsoram nr de elemente
////facem interschimbari pana cand totul ajunge la loc
////MAX HEAP SORT - atunci cand elementele coase din heap sunt scoase ordonate crescator
////descresctor cu MIN
//Avion extrageAvionCuAscundere(Heap* heap) {
//	if (heap->nrElemente > 0) {
//		Avion aux = heap->vector[0];
//		heap->vector[0] = heap->vector[heap->nrElemente - 1];
//		heap->vector[heap->nrElemente - 1] = aux;
//		heap->nrElemente--;
//		for (int i = (heap->nrElemente - 2) / 2; i >= 0; i--) {
//			filtrareHeap(*heap, i);
//		}
//		return aux;//shallow copy
//	}
//}
//
//void dezalocareHeap(Heap* heap) {
//	for (int i = 0; i < heap->lungime; i++) {
//		free(heap->vector[i].nume);
//		free(heap->vector[i].pretBilet);
//	}
//	free(heap->vector);
//	heap->vector = NULL;
//	heap->lungime = 0;
//	heap->nrElemente = 0;
//}
//
//int main() {
//	Heap heap = citireAvioaneDinFiiser("avioane.txt");
//	afiseazaHeap(heap);
//	printf("\n------Masini extrase------\n");
//	afisareAvion(extrageAvionCuAscundere(&heap));
//	afisareAvion(extrageAvionCuAscundere(&heap));
//	printf("\n------Avioane ascunse------\n");
//	afiseazaHeapAscuns(heap);
//	dezalocareHeap(&heap);
//	return 0;
//}