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
typedef struct Nod Nod;

struct Nod {
	Masina info;
	Nod* next;
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

void afisareListaMasini(Nod* cap) {
	while (cap != NULL) {
		afisareMasina(cap->info);
		cap = cap->next;
	}

}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;

	if ((*cap) == NULL) {
		*cap = nou;
	}
	else {
		Nod* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
}

void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = *cap;
	*cap = nou;
}

void* citireListaMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* lista = NULL;
	while (!feof(f)) {
		adaugaLaInceputInLista(&lista, citireMasinaDinFisier(f));
	}
	fclose(f);

	return lista;

}

void dezalocareListaMasini(Nod** cap) {
	while ((*cap) != NULL) {
		Nod* aux = (*cap);
		*cap = (*cap)->next;
		free(aux->info.numeSofer);
		free(aux->info.model);
		free(aux);
	}
}

float calculeazaPretMediu(Nod* cap) {
	float suma = 0;
	int numarMasini = 0;
	if (cap) {
		suma += cap->info.pret;
		numarMasini++;
		cap = cap->next;
	}
	if (numarMasini > 0) {
		return suma / numarMasini;
	}
	return 0;
}

float calculeazaPretulMasinilorUnuiSofer(Nod* cap, const char* nume) {
	float suma = 0;
	while (cap) {
		if (strcmp(cap->info.numeSofer,nume)==0) {
			suma += cap->info.pret;
		}
		cap = cap->next;
	}
	
	return suma;
}

//revenim daca avem timp
//void stergeMasinaCuSeria() {
//
//}

int main() {

	Nod* cap = NULL;
	cap = citireListaMasiniDinFisier("masini.txt");
	afisareListaMasini(cap);
	printf("\nMedia pretului: %.2f", calculeazaPretMediu(cap));
	printf("\nPretul masinilor lui badescu: %.2f", calculeazaPretulMasinilorUnuiSofer(cap,"Gigel"));

	dezalocareListaMasini(&cap);


	return 0;
}