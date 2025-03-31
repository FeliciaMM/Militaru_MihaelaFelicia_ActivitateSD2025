//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//
//typedef struct StructuraMasina Masina;
//
//struct Nod {
//	Masina info;
//	struct Nod* next;
//	struct Nod* prev;
//};
//
//typedef struct Nod Nod;
//
//struct List {
//	Nod* first;
//	Nod* last;
//};
//
//typedef struct List List;
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	Masina m1;
//	fgets(buffer, 100, file);
//	char* aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	m1.nrUsi = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	m1.pret = atof(aux);
//
//	aux = strtok(NULL, sep);
//	m1.model = (char*)malloc(strlen(aux) + 1);
//	strcpy(m1.model, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = (char*)malloc(strlen(aux) + 1);
//	strcpy(m1.numeSofer, aux);
//
//	m1.serie = *strtok(NULL, sep);
//
//	return m1;
//}
//
//void afisare(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr usi: %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareListaMasini(List list) {
//	Nod* p = list.first;
//	while (p) {
//		afisare(p->info);
//		p = p->next;
//	}
//}
//
//void adaugaMasinaLista(List* list, Masina masinaNoua) {
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = masinaNoua;
//	nodNou->prev = list->last;
//	nodNou->next = NULL;
//	if (list->last) {
//		list->last->next = nodNou;
//	}
//	else {
//		list->first = nodNou;
//	}
//	list->last = nodNou;
//}
//
//List citireListaDublaFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	List list;
//	list.first = NULL;
//	list.last = NULL;
//	while (!feof(f)) {
//		adaugaMasinaLista(&list, citireMasinaDinFisier(f));
//	}
//	fclose(f);
//	return list;
//}
//
//void afisareListaDubla(List list) {
//	Nod* temp = list.last;
//	while (temp) {
//		afisare(temp->info);
//		temp = temp->prev;
//	}
//}
//
//void dezalocare(List* list) {
//	Nod* temp = list->first;
//	while (temp != NULL) {
//		Nod* next = temp->next;
//		free(temp->info.numeSofer);
//		free(temp->info.model);
//		free(temp);
//		temp = next;
//	}
//	list->first = NULL;
//	list->last = NULL;
//}
//
//
//
//int main() {
//	List list;
//	list = citireListaDublaFisier("masini.txt");
//	afisareListaDubla(list);
//	dezalocare(&list);
//
//	return 0;
//}
//
