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

//creare structura pentru un nod dintr-un arbore binar de cautare
typedef struct Nod Nod;
struct Nod {
	Nod* st;
	Nod* dr;
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
	m1.pret= atof(strtok(NULL, sep));
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


void adaugaMasinaInArbore(Nod* *radacina, Masina masinaNoua) {
	
	if ((*radacina) != NULL) {
		if (masinaNoua.id < (*radacina)->info.id) {
			adaugaMasinaInArbore(&((*radacina)->st), masinaNoua);
		}
		else if (masinaNoua.id > (*radacina)->info.id)
		{
			adaugaMasinaInArbore(&((*radacina)->dr), masinaNoua);
		}
		else {
			if ((*radacina)->info.model != NULL) {
				free((*radacina)->info.model);
			}
			if ((*radacina)->info.numeSofer != NULL) {
				free((*radacina)->info.numeSofer);
			}
			(*radacina)->info.nrUsi = masinaNoua.nrUsi;
			(*radacina)->info.pret = masinaNoua.pret;
			(*radacina)->info.serie = masinaNoua.serie;
			(*radacina)->info.model = (char*)malloc(strlen(masinaNoua.model) + 1);
			strcpy_s((*radacina)->info.model, strlen(masinaNoua.model) + 1, masinaNoua.model);
			(*radacina)->info.numeSofer = (char*)malloc(strlen(masinaNoua.numeSofer) + 1);
			strcpy_s((*radacina)->info.numeSofer,strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
		}
	}
	else {
		(*radacina) = malloc(sizeof(Nod));
		(*radacina)->info = masinaNoua;
		(*radacina)->info.model = (char*)malloc(strlen(masinaNoua.model) + 1);
		strcpy_s((*radacina)->info.model, strlen(masinaNoua.model) + 1, masinaNoua.model);
		(*radacina)->info.numeSofer = (char*)malloc(strlen(masinaNoua.numeSofer) + 1);
		strcpy_s((*radacina)->info.numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
		(*radacina)->st = NULL;
		(*radacina)->dr = NULL;
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* file = fopen(numeFisier, "r");
	Nod* radacina = NULL;
	while (!feof(file)) {
		Masina m = citireMasinaDinFisier(file);
		adaugaMasinaInArbore(&radacina, m);
		free(m.model);
		free(m.numeSofer);
	}
	fclose(file);
	return radacina;
}

void afisareMasiniInOrdine(Nod* radacina) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere
	if (radacina != NULL)
	{
		afisareMasiniInOrdine(radacina->st);
		afisareMasina(radacina->info);
		afisareMasiniInOrdine(radacina->dr);
	}
}

void afisareArborePreOrdine(Nod* radacina) {
	if (radacina != NULL) {
		afisareMasina(radacina->info);
		afisareArborePreOrdine(radacina->st);
		afisareArborePreOrdine(radacina->dr);
	}
}

void dezalocareArboreDeMasini(Nod** radacina) {
	//sunt dezalocate toate masinile si arborele de elemente
	if ((*radacina) != NULL)
	{
		dezalocareArboreDeMasini(&((*radacina)->st));
		dezalocareArboreDeMasini(&((*radacina)->dr));
		free((*radacina)->info.model);
		free((*radacina)->info.numeSofer);
		free(*radacina);
		*radacina = NULL;
	}
}

Masina getMasinaByID(Nod* radacina,int id) {
	Masina m;
	m.id = -1;
	if (id > radacina->info.id)
	{
		return getMasinaByID(radacina->dr, id);
	}
	else if(id<radacina->info.id){
		return getMasinaByID(radacina->st, id);
	}
	else {
		m = radacina->info;
		m.numeSofer = (char*)malloc(strlen(radacina->info.numeSofer) + 1);
		strcpy(m.numeSofer, radacina->info.numeSofer);

		m.model= (char*)malloc(strlen(radacina->info.model) + 1);
		strcpy(m.model, radacina->info.model);
		return m;
	}

	return m;
}

int determinaNumarNoduri(Nod* radacina) {
	if (radacina != NULL) {
		return  1 + determinaNumarNoduri(radacina->st) + determinaNumarNoduri(radacina->dr);
	}
	else {
		return 0;
	}
	
}

Nod* stergeNodDupaId(Nod* rad, int id) {
	if (rad) {
		if (id < rad->info.id) {
			rad->st = stergeNodDupaId(rad->st, id);
		}
		else if (id > rad->info.id) {
			rad->dr = stergeNodDupaId(rad->dr, id);
		}
		else {
			if (rad->st == NULL && rad->dr == NULL) {
				free(rad->info.model);
				free(rad->info.numeSofer);
				free(rad);
				return NULL;
			}
			else if (rad->st == NULL) {
				Nod* temp = rad->dr;
				free(rad->info.model);
				free(rad->info.numeSofer);
				free(rad);
				return temp;
			}
			else if (rad->dr == NULL) {
				Nod* temp = rad->st;
				free(rad->info.model);
				free(rad->info.numeSofer);
				free(rad);
				return temp;
			}
			else {
				Nod* minNode = rad->dr;
				while (minNode->st != NULL) {
					minNode = minNode->st;
				}
				free(rad->info.model);
				free(rad->info.numeSofer);
				rad->info.id = minNode->info.id;
				rad->info.nrUsi = minNode->info.nrUsi;
				rad->info.pret = minNode->info.pret;
				rad->info.serie = minNode->info.serie;
				rad->info.model = (char*)malloc(strlen(minNode->info.model) + 1);
				strcpy(rad->info.model, minNode->info.model);
				rad->info.numeSofer = (char*)malloc(strlen(minNode->info.numeSofer) + 1);
				strcpy(rad->info.numeSofer, minNode->info.numeSofer);
				rad->dr = stergeNodDupaId(rad->dr, minNode->info.id);
			}
		}
	}
	else {
		return NULL;
	}
	return rad;
	
}

int aflareInaltime(Nod* rad) {
	if (rad) {
		int inaltimeSt = aflareInaltime(rad->st);
		int inaltimeDr = aflareInaltime(rad->dr);
		return 1 + (inaltimeSt > inaltimeDr ? inaltimeSt : inaltimeDr);
	}
}

Nod* subarboreMaiInalt(Nod* rad) {
	if (rad == NULL) return NULL;

	int inaltimeSt = aflareInaltime(rad->st);
	int inaltimeDr = aflareInaltime(rad->dr);

	if (inaltimeSt >= inaltimeDr) {
		return rad->st;
	}
	else {
		return rad->dr;
	}
}

int numarNoduriSubordonate(Nod* radacina, int idCautat) {
	if (radacina == NULL) {
		return 0;
	}
	if (idCautat < radacina->info.id) {
		return numarNoduriSubordonate(radacina->st, idCautat);
	}
	else if (idCautat > radacina->info.id) {
		return numarNoduriSubordonate(radacina->dr, idCautat);
	}
	else {

		int total = determinaNumarNoduri(radacina);
		return total - 1;  
	}
}

int main() {
	Nod* arbore = citireArboreDeMasiniDinFisier("masini.txt");
	// afisareArborePreOrdine(arbore);
	afisareMasiniInOrdine(arbore);

	Masina m = getMasinaByID(arbore, 2);
	printf("\n\n---------------");
	afisareMasina(m);

	int i = determinaNumarNoduri(arbore);
	printf("\nnumar noduri: %d", i);

	printf("\n----------------------------------\n");

	arbore = stergeNodDupaId(arbore, 2);
	afisareArborePreOrdine(arbore);

	Nod* subarbore = subarboreMaiInalt(arbore);
	printf("\n--- Subarborele cu inaltime mai mare ---\n");
	afisareMasiniInOrdine(subarbore);

	int idRadacinaSubnoduri = 3;
	int nrNoduriSub = numarNoduriSubordonate(arbore, idRadacinaSubnoduri);
	printf("\n--- Noduri in subordinea nodului radacina %d este %d ---\n", idRadacinaSubnoduri,nrNoduriSub);


	dezalocareArboreDeMasini(&arbore);
	return 0;
}