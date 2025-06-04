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

typedef struct NodePrincipal NodePrincipal;

typedef struct NodeSecundar NodeSecundar;

struct NodeSecundar {
	NodePrincipal* info;
	NodeSecundar* next;
};


struct NodePrincipal {
	NodePrincipal* next;
	NodeSecundar* vecin;
	Masina info;
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

//1. 
// structuri necesare
//dorim stocarea unui graf intr-o lista de liste
//astfel avem nod ListaPrincipala si NodListaSecundara

//2.
//functii de inserare in liste
//si in principala si in secundara

NodePrincipal* inserareLaSfInListaPrincipala(NodePrincipal* cap, Masina info) {
	NodePrincipal* nou = (NodePrincipal*)malloc(sizeof(NodePrincipal));
	nou->info = info;
	nou->next = NULL;
	nou->vecin = NULL;

	if (!cap) return nou;
	NodePrincipal* p = cap;
	while (p->next) {
		p = p->next;
		p->next = nou;
		return cap;
	}
}

NodeSecundar* inserareLaInceputListaSecundara(NodeSecundar* cap, NodePrincipal* info) {
	NodeSecundar* nou = (NodeSecundar*)malloc(sizeof(NodeSecundar));
	nou->info = info;
	nou->next = NULL;

	nou->next = cap;
	return cap;
}

//3.
//functie de cautarea in lista principala dupa ID
void* cautaNodDupaID(NodePrincipal* listaPrincipala, int id) {
	while (listaPrincipala && listaPrincipala->info.id!=id) {
		listaPrincipala = listaPrincipala->next;
	}
	return listaPrincipala;
}

//4.
//inserare muchie
void inserareMuchie(void* listaPrincipala, int idStart, int idStop) {
	NodePrincipal* nodStart = cautaNodDupaID(listaPrincipala, idStart);
	NodePrincipal* nodStop = cautaNodDupaID(listaPrincipala, idStop);
	if (nodStart && nodStop) {
		nodStart->vecin = inserareLaInceputListaSecundara(nodStart->vecin, nodStop);
		nodStop->vecin = inserareLaInceputListaSecundara(nodStop->vecin, nodStart);
	}
}


void* citireNoduriMasiniDinFisier(const char* numeFisier) {
	NodePrincipal* listaPrincipala = NULL;
	FILE* file = fopen(numeFisier, "r");
	while (!feof(file)) {
		inserareLaSfInListaPrincipala(listaPrincipala, citireMasinaDinFisier(file));
	}
	fclose(file);
	return listaPrincipala;
}

void citireMuchiiDinFisier(NodePrincipal* listaPrincipala,const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste 
	//toate id-urile de start si stop pentru fiecare muchie
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* file = fopen(numeFisier, "r");
	while (!feof(file)) {
		int idStart;
		int idStop;

		fscanf(file, "%d %d", &idStart, &idStop);
		inserareMuchie(listaPrincipala, idStart, idStop);
	}
}

void stergereNodeSecundar(NodeSecundar** cap) {
	NodeSecundar* aux = (*cap)->next;
	while ((*cap)) {
		aux = (*cap)->next;
		free(*cap);
		(*cap) = aux;
	}
}

void dezalocareNoduriGraf(NodePrincipal** listaPrincipala) {
	NodePrincipal* aux;
	while ((*listaPrincipala)) {
		aux = (*listaPrincipala)->next;
		stergereNodeSecundar((*listaPrincipala)->vecin);
		if ((*listaPrincipala)->info.model) {
			free((*listaPrincipala)->info.model);
		}
		if ((*listaPrincipala)->info.numeSofer) {
			free((*listaPrincipala)->info.numeSofer);
		}
	}
	free(*listaPrincipala);
	(*listaPrincipala) = aux;
}

//Parcurgere in adancime
typedef struct Stiva Stiva;

struct Stiva {
	int id;
	Stiva* next;
};

//creare structura Stiva
//push si pop pentru stiva
int pop(Stiva** cap) {
	Stiva* temp= *cap;
	if (*cap) {
		*cap = (*cap)->next;
		int id = temp->id;
		free(temp);

	}else{
		return -1;
	}
	
	
}

void push(Stiva** cap, int idNou) {
	Stiva* p = (Stiva*)malloc(sizeof(Stiva));
	p->id = idNou;
	p->next = *cap;
	*cap = p;
}

int calculeazaNrNoduriGraf(NodePrincipal* listaPrincipala) {
	int count = 0;
	while (listaPrincipala) {
		count++;
		listaPrincipala = listaPrincipala->next;
	}
	return count;
}

void afisareGrafInAdancime(NodePrincipal* listaPrincipala, int idPlecare) {
	Stiva* stiva = NULL;
	int nrNoduri = calculeazaNrNoduriGraf(listaPrincipala);
	int* vizitate = (int*)malloc(sizeof(int)*nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	vizitate[idPlecare - 1] = 1;
	push(&stiva, idPlecare);
	while (stiva) {
		int idCurent = pop(stiva);
		NodePrincipal* nodCurent = cautaNodDupaID(listaPrincipala,idCurent);
		afisareMasina(nodCurent->info);
		NodeSecundar* temp = nodCurent->vecin;
		while (temp) {
			if (vizitate[temp->info->info.id-1] == 0) {
				push(&stiva, temp->info->info.id);
				vizitate[temp->info->info.id - 1] == 1;
			}
			temp = temp->next;
		}
	}
}




//Parcurgere in latime

//creare structura coada
//enqueue si dequeue pentru coada
typedef struct Stiva Coada;

void enqueue(Coada** coada, int id) {
	Coada* nou = (Coada*)malloc(sizeof(Coada));
	nou->id = id;
	Coada* aux = (*coada);
	if (aux) {
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		(*coada) = nou;
	}
	
}

int dequeue(Coada** coada) {
	int  id = pop(coada);
	return id;
}

void afisareGrafInLatime(NodePrincipal* listaPrincipala, int idPlecare) {
	Coada* coada = NULL;
	int nrNoduri = calculeazaNrNoduriGraf(listaPrincipala);
	int* vizitate = (int*)malloc(sizeof(int) * nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	vizitate[idPlecare - 1] = 1;
	push(&coada, idPlecare);
	while (coada) {
		int idCurent = dequeue(coada);
		NodePrincipal* nodCurent = cautaNodDupaID(listaPrincipala, idCurent);
		afisareMasina(nodCurent->info);
		NodeSecundar* temp = nodCurent->vecin;
		while (temp) {
			if (vizitate[temp->info->info.id - 1] == 0) {
				enqueue(&coada, temp->info->info.id);
				vizitate[temp->info->info.id - 1] == 1;
			}
			temp = temp->next;
		}
	}
}

int main() {
	NodePrincipal* graf = citireNoduriMasiniDinFisier("masini.txt");
	citireMuchiiDinFisier(graf, "muchii.txt");
	dezalocareNoduriGraf(&graf);

	afisareGrafInAdancime(graf, 1);
	afisareGrafInLatime(graf, 1);

	return 0;
}