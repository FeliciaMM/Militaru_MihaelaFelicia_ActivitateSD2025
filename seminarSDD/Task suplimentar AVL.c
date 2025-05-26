//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////nu trebuie ca elementele din fisier sa fie sortate crescator
////arborele binar de cautare echilibrat - vom avra nr aproape egal de nodruri
////si in stanga si in dreapta
////factorul de balans se calculeaza ca diferenta dintre nr de noduri 
////al fiecarui sub arbore pot fii numai +1, -1 si 0, daca e diferit, avem 
////dezechilibru
//
//struct Student {
//	int id;
//	char* nume;
//	int an;
//
//};
//
//typedef struct Student Student;
//typedef struct Node Node;
//
//struct Node {
//	Student info;
//	Node* st;
//	Node* dr;
//	int gradEchilibru;
//};
//
//
//
//Student citireStudentFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	Student s;
//	char* aux;
//	aux = strtok(buffer, sep);
//	s.id = atoi(aux);
//	aux = strtok(NULL, sep);
//	s.nume = (char*)malloc(strlen(aux) + 1);
//	strcpy(s.nume, aux);
//	aux = strtok(NULL, sep);
//	s.an = atoi(aux);
//	return s;
//}
//
//void afiseazaStudent(Student s) {
//	printf("Id: %d\n", s.id);
//	printf("Nume: %s\n", s.nume);
//	printf("An: %d\n\n", s.an);
//}
//
//
//Node* rotireLaDreapta(Node** rad) {
//	if (rad) {
//		Node* aux = (*rad)->st;
//		(*rad)->st = aux->dr;
//		aux->dr = (*rad);
//		(*rad) = aux;
//		(*rad)->gradEchilibru++;
//	}
//}
//
//Node* rotireLaStanga(Node** rad) {
//	if (rad) {
//		Node* aux = (*rad)->dr;
//		(*rad)->dr = aux->st;
//		aux->st = (*rad);
//		(*rad) = aux;
//		(*rad)->gradEchilibru--;
//	}
//}
//
//
//
//Node* inserareStudentInAVL(Node** rad,Student s) {
//	if (*rad) {
//		if (s.id < (*rad)->info.id) {
//			inserareStudentInAVL(&((*rad)->st), s);
//			(*rad)->gradEchilibru++;
//		}
//		else {
//			inserareStudentInAVL(&((*rad)->dr), s);
//			(*rad)->gradEchilibru--;
//		}
//		if ((*rad)->gradEchilibru == 2) {
//			if ((*rad)->st->gradEchilibru == 1) {
//				//cazul simplu
//				rotireLaDreapta(rad);
//			}
//			else {
//				//cazul mai complicat
//				rotireLaStanga(&((*rad)->st));
//				rotireLaDreapta(rad);
//			}
//		}
//		if ((*rad)->gradEchilibru == -2) {
//			if ((*rad)->dr->gradEchilibru == 1) {
//				rotireLaDreapta(&((*rad)->dr));
//			}
//			rotireLaStanga(rad);
//		}
//	}
//	else {
//		Node* nou = (Node*)malloc(sizeof(Node));
//		nou->info = s;
//		nou->st = nou->dr = NULL;
//		nou->gradEchilibru = 0;
//		(*rad) = nou;
//	}
//}
//
//
//
//
//Node* citireArboreDinFisier(const char* numeFisier) {
//	Node* rad = NULL;
//	FILE* file = fopen(numeFisier, "r");
//	while (!feof(file)) {
//		Student s = citireStudentFisier(file);
//		inserareStudentInAVL(&rad, s);
//	}
//	fclose(file);
//	return rad;
//}
//
//void afisareArboreInPreordine(Node* rad) {
//	if (rad) {
//		afiseazaStudent(rad->info);
//		afisareArboreInPreordine(rad->st);
//		afisareArboreInPreordine(rad->dr);
//	}
//}
//
//void dezalocareArbore(Node** rad) {
//	if (*rad) {
//		dezalocareArbore(&((*rad)->st));
//		dezalocareArbore(&((*rad)->dr));
//		free((*rad)->info.nume);
//		free(*rad);
//		*rad = NULL;
//	}
//	
//
//}
//
//int calculeazaInaltimeArbore(Node* rad) {
//	if (rad) {
//		int inaltimeSt = calculeazaInaltimeArbore(rad->st);
//		int inaltimeDr = calculeazaInaltimeArbore(rad->dr);
//		return 1 + (inaltimeSt > inaltimeDr ? inaltimeSt : inaltimeDr);
//	}
//	return 0;
//}
//
//Student cautaStudentById(Node* rad, int idCautat) {
//	Student gasit;
//	if (rad) {
//		
//		if (rad->info.id > idCautat) {
//			cautaStudentById(rad->st,idCautat);
//		}
//		if (rad->info.id < idCautat) {
//			cautaStudentById(rad->dr, idCautat);
//		}else{
//			gasit = rad->info;
//			gasit.nume = (char*)malloc(strlen(rad->info.nume) + 1);
//			strcpy(gasit.nume, rad->info.nume);
//			return gasit;
//		}
//		
//	}
//	return gasit;
//}
//
//int numarulDeNoduri(Node* rad) {
//	if (rad) {
//		return 1 + numarulDeNoduri(rad->st) + numarulDeNoduri(rad->dr);
//	}
//	return 0;
//}
//
//void inserareInVectorInOrdine(Node* rad, Student* vector, int* index) {
//	if (rad) {
//		inserareInVectorInOrdine(rad->st, vector, index);
//		vector[*index].id = rad->info.id;
//		vector[*index].an = rad->info.an;
//		vector[*index].nume = (char*)malloc(strlen(rad->info.nume) + 1);
//		strcpy(vector[*index].nume, rad->info.nume);
//		(*index)++;
//		inserareInVectorInOrdine(rad->dr, vector, index);
//	}
//}
//
//void inserareInVectorInPostOrdine(Node* rad, Student* vector, int* index) {
//	if (rad) {
//		inserareInVectorInPostOrdine(rad->st,vector,index);
//		inserareInVectorInPostOrdine(rad->dr,vector,index);
//		vector[*index].id = rad->info.id;
//		vector[*index].nume = (char*)malloc(strlen(rad->info.nume) + 1);
//		strcpy(vector[*index].nume, rad->info.nume);
//		vector[*index].an = rad->info.an;
//		(*index)++;
//
//	}
//}
//
//void inserareInVectorInPreOrdine(Node* rad, Student* vector, int* index) {
//	if (rad) {
//		vector[*index].id = rad->info.id;
//		vector[*index].nume = (char*)malloc(strlen(rad->info.nume) + 1);
//		strcpy(vector[*index].nume, rad->info.nume);
//		vector[*index].an = rad->info.an;
//		(*index)++;
//		inserareInVectorInPreOrdine(rad->st, vector, index);
//		inserareInVectorInPreOrdine(rad->dr, vector, index);
//	}
//}
//
//void dezalocareVector(Student* vector, int nrNoduri) {
//	for (int i = 0; i < nrNoduri - 1; i++) {
//		free(vector[i].nume);
//	}
//	free(vector);
//}
//
//typedef struct NodLista NodLista;
//struct NodLista {
//	Student info;
//	NodLista* next;
//};
//
//void inserareInLista(NodLista** cap, Student s) {
//	NodLista* nou = (NodLista*)malloc(sizeof(NodLista));
//	nou->info.id = s.id;
//	nou->info.nume = (char*)malloc(strlen(s.nume) + 1);
//	strcpy(nou->info.nume, s.nume);
//	nou->info.an= s.an;
//	nou->next = NULL;
//
//	if (*cap == NULL) {
//		*cap = nou;
//	}
//	else {
//		NodLista* temp = *cap;
//		while (temp->next) {
//			temp = temp->next;
//		}
//		temp->next = nou;
//	}
//}
//
//void inserareListaInOrdine(Node* rad, NodLista** cap) {
//	if (rad) {
//		inserareListaInOrdine(rad->st, cap);
//		inserareInLista(cap, rad->info);
//		inserareListaInOrdine(rad->dr, cap);
//	}
//}
//
//void afisareLista(NodLista* cap) {
//	while (cap) {
//		afiseazaStudent(cap->info);
//		cap = cap->next;
//	}
//}
//
//int main() {
//	Node* rad = citireArboreDinFisier("studenti.txt");
//	afisareArboreInPreordine(rad);
//	printf("Inaltime: %d", calculeazaInaltimeArbore(rad));
//	Student gasit = cautaStudentById(rad, 2);
//	printf("\n---------Nod gasit--------\n");
//	afiseazaStudent(gasit);
//
//	//IN ORDINE
//	int nrNoduri = numarulDeNoduri(rad);
//	Student* vectorInOrdine = (Student*)malloc(sizeof(Student) * nrNoduri);
//	int index = 0;
//	inserareInVectorInOrdine(rad, vectorInOrdine, &index);
//	printf("\n--------Vector studenti in ordine: -------------\n");
//	for (int i = 0; i < nrNoduri; i++) {
//		afiseazaStudent(vectorInOrdine[i]);
//	}
//	dezalocareVector(vectorInOrdine, nrNoduri);
//
//	//POSTORDINE
//	Student* vectorInPostOrdine = (Student*)malloc(sizeof(Student) * nrNoduri);
//	index = 0;
//	inserareInVectorInPostOrdine(rad, vectorInPostOrdine, &index);
//
//	printf("\n--------Vector studenti in PostOrdine: -------------\n");
//	for (int i = 0; i < nrNoduri; i++) {
//		afiseazaStudent(vectorInPostOrdine[i]);
//	}
//	dezalocareVector(vectorInPostOrdine, nrNoduri);
//	index = 0;
//
//	//PREORDINE 
//	Student* vectorInPreOrdine = (Student*)malloc(sizeof(Student) * nrNoduri);
//	inserareInVectorInPreOrdine(rad, vectorInPreOrdine, &index);
//	printf("\n--------Vector studenti in PreOrdine: -------------\n");
//	for (int i = 0; i < nrNoduri; i++) {
//		afiseazaStudent(vectorInPreOrdine[i]);
//	}
//	dezalocareVector(vectorInPreOrdine, nrNoduri);
//
//	//LISTA IN ORDINE
//	NodLista* lista = NULL;
//	inserareListaInOrdine(rad, &lista);
//	afisareLista(lista);
//	dezalocareArbore(&rad);
//	return 0;
//}