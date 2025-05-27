//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct Factura {
//	char* numeCompanie;
//	int zileScadenta;
//	float pret;
//	char* destinatar;
//	unsigned char tip;
//};
//
//typedef struct Factura Factura;
//typedef struct Heap Heap;
//
//struct Heap {
//	Factura* vector;
//	int lungime;
//	int nrElemente;
//};
//
//Factura citireFacturaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	char* aux;
//	Factura f;
//	fgets(buffer, 100, file);
//	aux = strtok(buffer, sep);
//	f.numeCompanie = (char*)malloc(strlen(aux) + 1);
//	strcpy(f.numeCompanie, aux);
//	aux = strtok(NULL, sep);
//	f.zileScadenta = atoi(aux);
//	aux = strtok(NULL, sep);
//	f.pret = atoi(aux);
//	aux = strtok(NULL, sep);
//	f.destinatar = (char*)malloc(strlen(aux) + 1);
//	strcpy(f.destinatar, aux);
//	f.tip = *strtok(NULL,sep);
//	return f;
//}
//
//void afiseazaFactura(Factura f) {
//	printf("Compania: %s\n", f.numeCompanie);
//	printf("Zile Scadenta: %d\n", f.zileScadenta);
//	printf("Pretul facturii: %.2f\n",f.pret);
//	printf("Destinatarul: %s\n", f.destinatar);
//	printf("Tip: %c\n\n", f.tip);
//}
//
//Heap initializareHeap(int lungime) {
//	Heap heap;
//	heap.lungime = lungime;
//	heap.nrElemente = 0;
//	heap.vector = (Factura*)malloc(sizeof(Factura) * lungime);
//	return heap;
//}
//
//void filtrareHeap(Heap heap, int poz) {
//	int fiuS = 2 * poz + 1;
//	int fiuD = 2 * poz + 2;
//	int min = poz;
//	if(fiuS < heap.nrElemente && heap.vector[fiuS].zileScadenta < heap.vector[min].zileScadenta){
//		min = fiuS;
//	}
//
//	if (fiuD < heap.nrElemente && heap.vector[fiuD].zileScadenta < heap.vector[min].zileScadenta) {
//		min = fiuD;
//	}
//
//	if (poz != min) {
//		Factura aux = heap.vector[poz];
//		heap.vector[poz] = heap.vector[min];
//		heap.vector[min] = aux;
//
//		if (min <= (heap.nrElemente - 2) / 2) {
//			filtrareHeap(heap, min);
//		}
//	}
//}
//
//
//Heap citireHeapDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	Heap heap = initializareHeap(10);
//	while (!feof(file)) {
//		heap.vector[heap.nrElemente++] = citireFacturaDinFisier(file);
//	}
//	fclose(file);
//	for (int i = (heap.nrElemente - 2) / 2; i >= 0; i--) {
//		filtrareHeap(heap, i);
//	}
//	return heap;
//}
//
//void afiseazaHeap(Heap heap) {
//	for (int i = 0; i < heap.nrElemente; i++) {
//		afiseazaFactura(heap.vector[i]);
//	}
//}
//
//void dezalocareHeap(Heap* heap) {
//	for (int i = 0; i < heap->nrElemente; i++) {
//		free(heap->vector[i].numeCompanie);
//		free(heap->vector[i].destinatar);
//	}
//	free(heap->vector);
//	heap->vector = NULL;
//	heap->nrElemente = 0;
//	heap->lungime = 0;
//}
//
//
//Factura ScoateFacturaInFunctieDeScadenta(Heap* heap, int zileScadentaCautate) {
//	int i = 1;
//	//parcurgem toate facturile
//	while (i < heap->nrElemente) {
//		if (heap->vector[i].zileScadenta < zileScadentaCautate) {
//			//eliberam factura gasita
//			free(heap->vector[i].numeCompanie);
//			free(heap->vector[i].destinatar);
//			//punem ultima facuta in locul ei
//			heap->vector[i] = heap->vector[heap->nrElemente - 1];
//			heap->nrElemente--;
//			//filtram iar
//			filtrareHeap(*heap, i);
//		}
//		else {
//			i++;
//		}
//	}
//	
//}
//
////typedef struct Node {
////	Factura info;
////	struct Node* st;
////	struct Node* dr;
////} Node;
////
////// Creează un nod nou
////Node* creareNode(Factura f) {
////	Node* nod = malloc(sizeof(Node));
////	nod->info = f;
////	nod->st = nod->dr = NULL;
////	return nod;
////}
////
////// Inserează recursiv în BST pe baza zileScadenta (sau oricărui alt criteriu)
////Node* insereazaInBST(Node* rad, Factura f) {
////	if (!rad) {
////		return creareNode(f);
////	}
////	if (f.zileScadenta < rad->info.zileScadenta) {
////		rad->st = insereazaInBST(rad->st, f);
////	}
////	else {
////		rad->dr = insereazaInBST(rad->dr, f);
////	}
////	return rad;
////}
////
////// Construiește întreg BST-ul din vectorul heap.vector[]
////Node* construireBSTdinHeap(Heap* heap) {
////	Node* rad = NULL;
////	for (int i = 0; i < heap->nrElemente; i++) {
////		rad = insereazaInBST(rad, heap->vector[i]);
////	}
////	return rad;
////}
////
////// Traversare în ordine (ca să afișezi facturile sortate după zileScadenta)
////void inordine(Node* rad) {
////	if (!rad) return;
////	inordine(rad->st);
////	afiseazaFactura(rad->info);
////	inordine(rad->dr);
////}
////
////// Nu uita să dezaloci și BST-ul la final:
////void dezalocareBST(Node* rad) {
////	if (!rad) return;
////	dezalocareBST(rad->st);
////	dezalocareBST(rad->dr);
////	free(rad);
////}
//
//
//int main() {
//	Heap heap = citireHeapDinFisier("facturi.txt");
//	afiseazaHeap(heap);
//	ScoateFacturaInFunctieDeScadenta(&heap,3);
//	printf("\nDupa scoaterea facturilor cu o anume scadenta: \n");
//	afiseazaHeap(heap);
//	dezalocareHeap(&heap);
//	return 0;
//}