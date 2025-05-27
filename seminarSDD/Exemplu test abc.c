#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//13
struct Fotografie {
	int id;
	char* oras;
	float rezolutie;
};

typedef struct Fotografie Fotografie;
typedef struct Node Node;

struct Node {
	Fotografie info;
	Node* st;
	Node* dr;
};

Fotografie citireFotografieFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	Fotografie f;
	fgets(buffer, 100, file);
	aux = strtok(buffer, sep);
	f.id = atoi(aux);
	aux = strtok(NULL, sep);
	f.oras = (char*)malloc(strlen(aux) + 1);
	strcpy(f.oras, aux);
	aux = strtok(NULL, sep);
	f.rezolutie = atof(aux);
	return f;
}

void afiseazaFoto(Fotografie f) {
	printf("Id: %d\n", f.id);
	printf("Oras: %s\n", f.oras);
	printf("Rezolutie: %.2f\n\n", f.rezolutie);
}

void adaugareNodInArbore(Node** rad, Fotografie f) {
	if (*rad) {
		if (f.id < (*rad)->info.id) {
			adaugareNodInArbore(&((*rad)->st), f);
		}
		else if(f.id > (*rad)->info.id){
			adaugareNodInArbore(&((*rad)->dr), f);
			}
		else {
			if ((*rad)->info.oras != NULL) {
				free((*rad)->info.oras);
			}
			(*rad)->info.id = f.id;
			(*rad)->info.oras = (char*)malloc(strlen(f.oras) + 1);
			strcpy((*rad)->info.oras, f.oras);
			(*rad)->info.rezolutie = f.rezolutie;
		}
	}
	else {
		(*rad) = malloc(sizeof(Node));
		(*rad)->info = f;
		(*rad)->info.oras = (char*)malloc(strlen(f.oras) + 1);
		strcpy((*rad)->info.oras, f.oras);
		(*rad)->st = NULL;
		(*rad)->dr = NULL;
	}
}

Node* citireArboreDinFisier(const char* numeFisier) {
	Node* rad = NULL;
	FILE* file = fopen(numeFisier, "r");
	while (!feof(file)) {
		Fotografie f = citireFotografieFisier(file);
		adaugareNodInArbore(&rad, f);
	}
	fclose(file);
	return rad;

}

void afiseazaArboreInOrder(Node* rad) {
	if (rad) {
		afiseazaArboreInOrder(rad->st);
		afiseazaFoto(rad->info);
		afiseazaArboreInOrder(rad->dr);

	}
}	

void afiseazaArborePreOrder(Node* rad) {
	if (rad) {
		afiseazaFoto(rad->info);
		afiseazaArborePreOrder(rad->st);
		afiseazaArborePreOrder(rad->dr);

	}
}

void dezalocareArbore(Node** rad) {
	if ((*rad)!=NULL) {
		dezalocareArbore(&((*rad)->st));
		dezalocareArbore(&((*rad)->dr));
		free((*rad)->info.oras);
		free((*rad));
		(*rad) = NULL;
		

	}
}

int numarulDeFotografiiInAcelasiOras(Node* rad, const char* oras) {
	int nrPoze = 0;
	if (rad){
		if (strcmp(rad->info.oras,oras)==0) {
			nrPoze++;
		}
		nrPoze += numarulDeFotografiiInAcelasiOras(rad->st,oras);
		nrPoze += numarulDeFotografiiInAcelasiOras(rad->dr, oras);
		
	}
	return nrPoze;
}

void modificaOrasById(Node* rad, int idCautat, const char* orasNou) {
	if (rad) {
		if (rad->info.id == idCautat) {
			free(rad->info.oras);
			rad->info.oras = (char*)malloc(strlen(orasNou) + 1);
			strcpy(rad->info.oras, orasNou);
		}
		modificaOrasById(rad->st, idCautat, orasNou);
		modificaOrasById(rad->dr, idCautat, orasNou);
	}
}

Node* stergereaUnuiNodeById(Node* rad, int idSters) {
	if (rad == NULL)
		return NULL;

	if (idSters < rad->info.id) {
		rad->st = stergereaUnuiNodeById(rad->st, idSters);
	}
	else if (idSters > rad->info.id) {
		rad->dr = stergereaUnuiNodeById(rad->dr, idSters);
	}
	else {
		// Nodul cu id-ul căutat a fost găsit
		if (rad->st == NULL && rad->dr == NULL) {
			// frunză
			free(rad->info.oras);
			free(rad);
			return NULL;
		}
		else if (rad->st == NULL) {
			Node* temp = rad->dr;
			free(rad->info.oras);
			free(rad);
			return temp;
		}
		else if (rad->dr == NULL) {
			Node* temp = rad->st;
			free(rad->info.oras);
			free(rad);
			return temp;
		}
		else {
			// are ambii fii
			Node* succesor = rad->dr;
			while (succesor->st != NULL)
				succesor = succesor->st;

			// copiere info succesor
			free(rad->info.oras);
			rad->info.id = succesor->info.id;
			rad->info.oras = (char*)malloc(strlen(succesor->info.oras) + 1);
			strcpy(rad->info.oras, succesor->info.oras);
			rad->info.rezolutie = succesor->info.rezolutie;

			// ștergem recursiv succesorul
			rad->dr = stergereaUnuiNodeById(rad->dr, succesor->info.id);
		}
	}
	return rad;
}

int main() {
	Node* arbore = citireArboreDinFisier("fotografii.txt");
	afiseazaArborePreOrder(arbore);

	int nrFotoBuc = numarulDeFotografiiInAcelasiOras(arbore, "Bucuresti");
	printf("\nNr poze bucuresti: %d", nrFotoBuc);


	printf("\n------MODIFICARE ORAS------\n");
	modificaOrasById(arbore, 1, "AAAA");
	afiseazaArborePreOrder(arbore);
	printf("\n------STERGERE------\n");
	Node* arboredupasters = stergereaUnuiNodeById(arbore, 1);
	afiseazaArborePreOrder(arboredupasters);
	dezalocareArbore(&arbore);
	
	return 0;
}