#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};

typedef struct StructuraMasina Masina;

struct Nod {
	Masina info;
	struct Nod* next;
	struct Nod* prev;
};

typedef struct Nod Nod;

struct List {
	Nod* first;
	Nod* last;
};

typedef struct List List;

// Citire masina din fisier
Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	Masina m1;

	if (fgets(buffer, 100, file) == NULL) {
		m1.model = NULL;
		m1.numeSofer = NULL;
		return m1;
	}

	char* aux = strtok(buffer, sep);
	m1.id = atoi(aux);

	aux = strtok(NULL, sep);
	m1.nrUsi = atoi(aux);

	aux = strtok(NULL, sep);
	m1.pret = atof(aux);

	aux = strtok(NULL, sep);
	m1.model = (char*)malloc(strlen(aux) + 1);
	strcpy(m1.model, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = (char*)malloc(strlen(aux) + 1);
	strcpy(m1.numeSofer, aux);

	m1.serie = *strtok(NULL, sep);

	return m1;
}

void afisare(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr usi: %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(List list) {
	Nod* p = list.first;
	while (p) {
		afisare(p->info);
		p = p->next;
	}
}

void adaugaInListaCrescatorUsi(List* list, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;
	nou->prev = NULL;

	if (list->first == NULL) {
		list->first = nou;
		list->last = nou;
		return;
	}
	Nod* temp = list->first;

	while (temp != NULL && temp->info.nrUsi < masinaNoua.nrUsi) {
		temp = temp->next;
	}

	if (temp == list->first) {
		nou->next = list->first;
		list->first->prev = nou;
		list->first = nou;
		return;
	}

	if (temp == NULL) {
		nou->prev = list->last;
		list->last->next = nou;
		list->last = nou;
		return;
	}

	nou->next = temp;
	nou->prev = temp->prev;
	temp->prev->next = nou;
	temp->prev = nou;
}

List citireListaDublaFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	List list;
	list.first = NULL;
	list.last = NULL;

	while (!feof(f)) {
		Masina masinaNoua = citireMasinaDinFisier(f);
		if (masinaNoua.model != NULL) { 
			adaugaInListaCrescatorUsi(&list, masinaNoua);
		}
	}

	fclose(f);
	return list;
}

void afisareListaDubla(List list) {
	Nod* temp = list.last;
	while (temp) {
		afisare(temp->info);
		temp = temp->prev;
	}
}

void dezalocare(List* list) {
	Nod* temp = list->first;
	while (temp != NULL) {
		Nod* next = temp->next;
		free(temp->info.numeSofer);
		free(temp->info.model);
		free(temp);
		temp = next;
	}
	list->first = NULL;
	list->last = NULL;
}

void stergeUnNod(List* lista, int indexNod) {
	if (lista->first == NULL) {
		printf("Lista este goala.\n");
		return;
	}

	Nod* temp = lista->first;
	int count = 0;

	while (temp != NULL && count < indexNod) {
		temp = temp->next;
		count++;
	}
	if (temp == NULL) {
		printf("Indexul este in afara listei.\n");
		return;
	}

	if (lista->first == lista->last) {
		lista->first = NULL;
		lista->last = NULL;
	}
	else if (temp == lista->first) {
		lista->first = temp->next;
		lista->first->prev = NULL;
	}
	else if (temp == lista->last) {
		lista->last = temp->prev;
		lista->last->next = NULL;
	}
	else {
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	free(temp->info.numeSofer);
	free(temp->info.model);
	free(temp);
}


int main() {
	List list = citireListaDublaFisier("masini.txt");
	afisareListaDubla(list);

	stergeUnNod(&list, 2);
	printf("Lista dupa stergere:\n");
	afisareListaDubla(list);


	dezalocare(&list);

	return 0;
}
