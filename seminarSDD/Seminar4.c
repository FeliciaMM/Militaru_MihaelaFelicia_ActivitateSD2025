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
	 Nod* urm;
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
	while (cap) {
		afisareMasina(cap->info);
		cap = cap->urm;
	}
}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->urm = NULL;
	
	if(*cap == NULL) {
		*cap = nou;
	}else {
		Nod* p = *cap;
		while (p->urm) {
			p = p->urm;
		}
		p->urm = nou;
	}
}

void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->urm = *cap;
	*cap = nou;

}

void* citireListaMasiniDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* lista = NULL;
	while(!feof(file)) {
		adaugaLaInceputInLista(&lista, citireMasinaDinFisier(file));

	}
	fclose(file);
	return lista;
}

void dezalocareListaMasini(Nod** cap) {
	while((*cap) != NULL) {
		Nod* temp = *cap;
		*cap = (*cap)->urm;
		free(temp->info.model);
		free(temp->info.numeSofer);
		free(temp);
	}
}

float calculeazaPretMediu(Nod* lista) {
	if (!lista) return 0;
	int count = 0;
	int sum = 0;
	while (lista) {
		sum += lista->info.pret;
		count++;
		lista = lista->urm;
	}
	return 0;
}

void stergeMasiniDinSeria(/*lista masini*/ char serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

float calculeazaPretulMasinilorUnuiSofer(Nod* lista, const char* numeSofer) {
	float sum = 0;
	while (lista) {
		if (strcmp(lista->info.numeSofer, numeSofer) == 0) {
			sum += lista->info.pret;
		}
		lista = lista->urm;
	}
	return sum;
}



int main() {
	Nod* cap = NULL;
	cap = citireListaMasiniDinFisier("masini.txt");
	afisareListaMasini(cap);
	dezalocareListaMasini(&cap);
	printf("%f\n",calculeazaPretMediu(cap));
	printf("%f\n", calculeazaPretulMasinilorUnuiSofer(cap,"Ionel"));
	return 0;
}