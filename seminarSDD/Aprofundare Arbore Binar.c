#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//preordine - rsd
//inordine - srd
//postordine - sdr

struct Avion {
	char* model;
	int nrLocuri;
	int nrLocuriOcupate;
	float* preturiBilete;
};
typedef struct Avion Avion;
typedef struct Node Node;

struct Node {
	Node* l;
	Node* r;
	Avion info;
};

//pentru eventualitatea in care vrem sa initializam

Avion initializare(const char* model, int nrLocuri, int nrLocuriOcupate, float* preturiBilete) {
	Avion a;
	a.model = (char*)malloc(sizeof(char) * (strlen(model) + 1));
	strcpy(a.model, model);
	a.nrLocuri = nrLocuri;
	a.nrLocuriOcupate = nrLocuriOcupate;
	a.preturiBilete = (float*)malloc(nrLocuriOcupate * sizeof(float));
	for (int i = 0; i < nrLocuriOcupate; i++) {
		a.preturiBilete[i] = preturiBilete[i];
	}
	return a;
}



void afisareAvion(Avion avion) {
	printf("Modelul: %s\n", avion.model);
	printf("Nr Locuri: %d\n", avion.nrLocuri);
	printf("Nr Locuri Ocupate: %d\n", avion.nrLocuriOcupate);
	printf("Preturile biletelor:\n");
	for (int i = 0; i < avion.nrLocuriOcupate; i++) {
		printf("%.2f ", avion.preturiBilete[i]);
	}
	printf("\n");
}

Avion citireAvionDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Avion a;
	aux = strtok(buffer, sep);
	
	a.model = (char*)malloc(strlen(aux) + 1);
	strcpy(a.model, aux);
	aux = strtok(NULL, sep);
	a.nrLocuri = atoi(aux);
	aux = strtok(NULL, sep);
	a.nrLocuriOcupate = atoi(aux);
	a.preturiBilete = NULL;
	if (a.nrLocuriOcupate > 0) {
		a.preturiBilete = (float*)malloc(a.nrLocuriOcupate * sizeof(float));
		for (int i = 0; i < a.nrLocuriOcupate; i++) {
			 aux = strtok(NULL, sep);
			 if (aux != NULL) {
				 a.preturiBilete[i] = atof(aux);
			 }

		}
	}
	return a;
}

Node* inserareAvionInArbore(Node* rad, Avion a) {
	if (rad) {
		if (rad->info.nrLocuri > a.nrLocuri) {
			rad->l = inserareAvionInArbore(rad->l, a);
		}
		else {
			rad->r = inserareAvionInArbore(rad->r, a);
		}
		return rad;
	}
	else {
		Node* nou = (Node*)malloc(sizeof(Node));
		nou->info = a;
		nou->r = NULL;
		nou->l = NULL;
		return nou;
	}
}

Node* citireArboreDinFisier(const char* numeFisier) {
	Node* rad = NULL;
	FILE* file = fopen(numeFisier, "r");
	if (file) {
		while (!feof(file)) {
			rad = inserareAvionInArbore(rad, citireAvionDinFisier(file));
			
		}
	}
	fclose(file);
	return rad;
}

void afisareArbore(Node* rad) {
	if (rad) {
		//le schimbam in functie de ordinea in care dorim sa afisam
		afisareArbore(rad->l);
		afisareAvion(rad->info);
		afisareArbore(rad->r);
	}
}

Avion cautareAvionInArboreDupaNrLocuri(Node* rad, int nrLocuri) {
	if (rad) {
		if (rad->info.nrLocuri == nrLocuri) {
			Avion a = initializare(rad->info.model, rad->info.nrLocuri, rad->info.nrLocuriOcupate, rad->info.preturiBilete);//deepcopy
			return a;
		}
		else if (rad->info.nrLocuri > nrLocuri) {
			return cautareAvionInArboreDupaNrLocuri(rad->l, nrLocuri);
		}
		else {
			return cautareAvionInArboreDupaNrLocuri(rad->r, nrLocuri);
		}
	}
	else {
		return initializare("", -1, -1, NULL);
	}
}

void dezalocare(Node** rad) {
	if ((*rad) != NULL) {
		dezalocare(&((*rad)->l));
		dezalocare(&((*rad)->r));
		free((*rad)->info.model);
		free((*rad)->info.preturiBilete);
		free(*rad);
		*rad = NULL;
	}
}

void main() {
	Avion a = initializare("A330", 300, 3, (float[]) { 10, 20, 30 });
	afisareAvion(a);


	Node* arbore = citireArboreDinFisier("avioane.txt");
	afisareArbore(arbore);

	//FILE* file = fopen("avioane.txt", "r");
	//if (file) {
	//	Avion avion;
	//	while (!feof(file)) {
	//		avion = citireAvionDinFisier(file);
	//		if (avion.model != NULL) {
	//			afisareAvion(avion);
	//			free(avion.model);
	//			free(avion.preturiBilete);
	//		}
	//	}
	//}
	//else {
	//	perror("Nu exista fisier");
	//	return;
	//}
	//fclose(file);

	printf("\nAvion vautua: ");
	Avion cautare = cautareAvionInArboreDupaNrLocuri(arbore, 200);
	afisareAvion(cautare);
	free(cautare.model);
	free(cautare.preturiBilete);
	dezalocare(&arbore);
}