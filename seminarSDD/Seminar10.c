#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

typedef struct Nod Nod;
//STACK - STIVA
struct Nod {
	Masina info;
	Nod* next;
};

typedef struct NodDublu NodDublu;
typedef struct ListaDubla ListaDubla;
struct NodDublu {
	Masina info;
	NodDublu* next;
	NodDublu* prev;
};

struct ListaDubla {
	NodDublu* first;
	NodDublu* last;
};

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

//STACK
//Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
//putem reprezenta o stiva prin LSI, LDI sau vector
void pushStack(Nod** stiva, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masina;
	nou->next = (*stiva);
	(*stiva) = nou;
}

Masina popStack(Nod** stiva) {
	Masina m;
	if ((*stiva) != NULL) {
		Nod* temp = *stiva;
		m = temp->info;
		*stiva = temp->next;
		free(temp);
	}
	else {
		m.id = -1;
		m.nrUsi = 0;
		m.pret = 0.0f;
		m.model = NULL;
		m.numeSofer = NULL;
		m.serie = 0;
	}
	return m;
}

unsigned char emptyStack(Nod* stiva) {
	return stiva == NULL;
}

Nod* citireStackMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* stiva = NULL;
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		pushStack(&stiva, m);
	}
	fclose(f);
	return stiva;
}

void dezalocareStivaDeMasini(Nod** stiva) {
	while ((*stiva) != NULL) {
		Masina m = popStack(stiva);
		free(m.numeSofer);
		free(m.model);

	}
}

int size(Nod* stiva) {
	int nr = 0;
	while (stiva->next != NULL) {
		nr++;
	}
	return nr;
}

//QUEUE
//Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
//putem reprezenta o coada prin LSI, LDI sau vector
void enqueue(ListaDubla* coada, Masina masina) {
	NodDublu* nou = (NodDublu*)malloc(sizeof(NodDublu));
	nou->info = masina;
	nou->prev = coada->last;
	nou->next = NULL;
	if (coada->last != NULL) {
		coada->last->next = nou;
		coada->last = nou;
	}
	else {
		coada->first = nou;

	}
	coada->last = nou;
	
}

Masina dequeue(ListaDubla* coada) {
	Masina m;
	m.id = -1;
	if (coada->first != NULL) {
		m = coada->first->info;
		NodDublu* aux = coada->first;
		if (coada->first->next != NULL) {
			coada->first = coada->first->next;
			coada->first->prev = NULL;
		}
		else {
			coada->first = NULL;
			coada->last = NULL;
		}
		free(aux);
	}
	return m;
}

ListaDubla citireCoadaDeMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	ListaDubla coada;
	coada.first = NULL;
	coada.last = NULL;
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		enqueue(&coada, m);
	}
	fclose(f);
	return coada;
}

void dezalocareCoadaDeMasini(ListaDubla* coada) {
	NodDublu* aux = coada->last;
	while (aux) {
		NodDublu* temp = aux;
		aux = aux->prev;
		free(temp->info.model);
		free(temp->info.numeSofer);
		free(temp);
	}
	coada->first = NULL;
	coada->last = NULL;
}


//metode de procesare
Masina getMasinaByID(/*stiva sau coada de masini*/int id);

float calculeazaPretTotal(ListaDubla* coada) {
	float suma = 0;
	ListaDubla nou;
	nou.first = NULL;
	nou.last = NULL;
	while ((*coada).first) {
		Masina m = dequeue(coada);
		suma += m.pret;
		enqueue(&nou,m);

	}
	coada->first = nou.first;
	coada->last = nou.last;

	return suma;
}

int main() {
	/*Nod* stiva = citireStackMasiniDinFisier("masini.txt");
	Masina m = popStack(&stiva);
	afisareMasina(m);
	printf("Nr noduri: %d", size(stiva));*/


	ListaDubla coada = citireCoadaDeMasiniDinFisier("masini.txt");
	Masina md = dequeue(&coada);
	afisareMasina(md);

	printf("Suma preturi: %.2f", calculeazaPretTotal(&coada));
	dezalocareCoadaDeMasini(&coada);
	/*dezalocareStivaDeMasini(&stiva);*/
	return 0;
}