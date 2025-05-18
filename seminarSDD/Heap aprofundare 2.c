#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//poz*2-1 - fiu
//poz*2-2 - fiu
//(nrElemente-2)/2 verifica cate noduri sunt parinti
struct Student {
	int id;
	char* nume;
	int an;
};

typedef struct Student Student;

struct Heap {
	int lungime;
	int nrElemente;
	Student* vector; 
};

typedef struct Heap Heap;

Student citireStudentDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Student s;
	aux = strtok(buffer, sep);
	s.id = atoi(aux);
	aux = strtok(NULL, sep);
	s.nume = (char*)malloc(strlen(aux) + 1);
	strcpy(s.nume, aux);
	aux = strtok(NULL, sep);
	s.an = atoi(aux);

	return s;
}

void afiseazaStudent(Student s) {
	printf("\nStudent: %s", s.nume);
	printf("\nId: %d", s.id);
	printf("\nAnul: %d", s.an);
}

Heap initializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.nrElemente = 0;
	//trebuie alocata memorie pt heap cu sizeof struct-ul nostru * lungime
	heap.vector = (Student*)malloc(sizeof(Student)*heap.lungime);
	return heap;
}

void filtrareHeap(Heap heap,int poz) {
	int pozFius = poz * 2 - 1;
	int pozFiud = poz * 2 - 2;
	//cautam pozitia maxima incepand cu nodul care ni se da
	int pozMaxim = poz;
	//daca fii au val mai mare, mutam poz maxima pe pozitia lor
	if (pozFius <= heap.lungime && heap.vector[pozFius].id > heap.vector[pozMaxim].id) {
		pozMaxim = pozFius;
	}
	if (pozFiud < heap.nrElemente && heap.vector[pozFiud].id > heap.vector[pozMaxim].id) {
		pozMaxim = pozFiud;
	}
	if (pozMaxim < poz) {
		Student aux = heap.vector[pozMaxim];
		heap.vector[pozMaxim] = heap.vector[poz];
		heap.vector[poz] = aux;
		//verificam daca maximul mai are fii si daca trebuie mutati
		//pozMax <= (nrElemente-2)/2 verifica daca poz este nod parinte sau frunza
		//(7 - 2) / 2 = 2
		//Deci nodurile de la index 0, 1, și 2 pot avea fii
		//Nodurile 3, 4, 5, 6 sunt frunze(nu au fii)
		if (pozMaxim <= (heap.nrElemente - 2) / 2) {
			filtrareHeap(heap, pozMaxim);
		}
	}
}

Heap citireHeapDinFisier(char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Heap heap = initializareHeap(10);
	if (file) {
		while (!feof(file)) {
			Student s = citireStudentDinFisier(file);
			heap.vector[heap.nrElemente++] = s;
		}
		fclose(file);
		//trecem prin toate nodurile parinte
		for (int i = (heap.nrElemente - 2) / 2; i >= 0; i--) {
			filtrareHeap(heap, i);
		}
	}
	return heap;
}

Student extragereStudentDinHeap(Heap* heap) {
	//interschimbare intre primul si ultimul element;
	if (heap->nrElemente > 0) {
		Student aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->nrElemente - 1];
		heap->vector[heap->nrElemente - 1] = aux;
		heap->nrElemente--;
		for (int i = (heap->nrElemente - 2) / 2; i >= 0; i--) {
			filtrareHeap(*heap, i);
		}
		return aux;
	}	
}

void dezalocareHeap(Heap* heap) {
	for (int i = 0; i < heap->lungime; i++) {
		free(heap->vector[i].nume);
	}
	free(heap->vector);
	heap->vector = NULL;
	heap->lungime = 0;
	heap->nrElemente = 0;
}

void afiseazaHeap(Heap heap) {
	for (int i = 0; i < heap.nrElemente; i++) {
		printf("\n");
		afiseazaStudent(heap.vector[i]);
	}
}

int main() {
	Heap heap = citireHeapDinFisier("studenti.txt");
	afiseazaHeap(heap);

	printf("--------element scos-------");
	Student scos = extragereStudentDinHeap(&heap);
	afiseazaStudent(scos);
	dezalocareHeap(&heap);
	return 0;
}