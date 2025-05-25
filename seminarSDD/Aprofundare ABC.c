//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct Student {
//	int id;
//	char* nume;
//	int an;
//};
//typedef struct Student Student;
//typedef struct Node Node;
//
//struct Node {
//	Student info;
//	Node* st;
//	Node* dr;
//};
//
//Student initializareStudent(int id, const char* nume, int an) {
//	Student s;
//	s.id = id;
//	s.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
//	strcpy(s.nume, nume);
//	s.an = an;
//
//	return s;
//}
//
//Student citireStudentDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Student s;
//	aux = strtok(buffer, sep);
//	s.id = atoi(aux);
//	aux = strtok(NULL, sep);
//	s.nume = (char*)malloc(strlen(aux) + 1);
//	strcpy(s.nume, aux);
//	aux = strtok(NULL, sep);
//	s.an = atoi(aux);
//
//	return s;
//}
//
//void afiseazaStudent(Student s) {
//	printf("\nId: %d", s.id);
//	printf("\nNume: %s", s.nume);
//	printf("\nAn: %d\n", s.an);
//}
//
//Node* inserareStudentInArbore(Node** rad, Student s) {
//	if ((*rad)!=NULL) {
//		if (s.id < (*rad)->info.id) {
//			inserareStudentInArbore(&((*rad)->st), s);
//		}
//		else if(s.id>(*rad)->info.id){
//			inserareStudentInArbore(&((*rad)->dr),s);
//		}
//		else {
//			if ((*rad)->info.nume != NULL) {
//				free((*rad)->info.nume);
//			}
//			(*rad)->info.id = s.id;
//			(*rad)->info.nume = (char*)malloc(strlen(s.nume) + 1);
//			strcpy((*rad)->info.nume, s.nume);
//			(*rad)->info.an = s.an;
//		}
//	}
//	else {
//		(*rad) = malloc(sizeof(Node));
//		(*rad)->info = s;
//		(*rad)->info.nume = (char*)malloc(strlen(s.nume) + 1);
//		strcpy((*rad)->info.nume, s.nume);
//		(*rad)->st = NULL;
//		(*rad)->dr = NULL;
//	}
//}
//
//Node* citireArboreStudentiDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	Node* rad = NULL;
//	while (!feof(file)) {
//		Student s = citireStudentDinFisier(file);
//		inserareStudentInArbore(&rad, s);
//	}
//	fclose(file);
//	return rad;
//}
//
////SRD - in ordine, radacina e in
//void afiseazaArboreInOrdine(Node* radacina) {
//	if (radacina!=NULL) {
//		afiseazaArboreInOrdine(radacina->st);
//		afiseazaStudent(radacina->info);
//		afiseazaArboreInOrdine(radacina->dr);
//	}
//}
//
////RSD
//void afiseazaInPreordine(Node* radacina) {
//	if (radacina != NULL) {
//		afiseazaStudent(radacina->info);
//		afiseazaInPreordine(radacina->st);
//		afiseazaInPreordine(radacina->dr);
//	}
//}
//
////SDR
//void afiseazaInPostordina(Node* radacina) {
//	if (radacina != NULL) {
//		afiseazaInPreordine(radacina->st);
//		afiseazaInPreordine(radacina->dr);
//		afiseazaStudent(radacina->info);
//	}
//}
//
////cautare in arbore binar
//Student cautareStudentDupaId(Node* radacina, int idCautat) {
//	Student s;
//	s.id = -1;
//	s.nume = NULL; 
//	s.an = -1;
//	if (radacina) {
//		if (radacina->info.id == idCautat) {
//			s = radacina->info;
//			s.nume = (char*)malloc(strlen(radacina->info.nume) + 1);
//			strcpy(s.nume, radacina->info.nume);
//			
//			return s;
//		}
//		else if (radacina->info.id < idCautat) {
//			return cautareStudentDupaId(radacina->dr, idCautat);
//		}
//		else {
//			return cautareStudentDupaId(radacina->st, idCautat);
//		}
//	}
//	else {
//		return s;
//	}
//}
//
//void dezalocareArbore(Node** rad) {
//	if ((*rad)) {
//		dezalocareArbore(&((*rad)->st));
//		dezalocareArbore(&((*rad)->dr));
//		free((*rad)->info.nume);
//		free(*rad);
//		*rad = NULL;
//	}
//}
//
//
//int main() {
//	Student s1 = initializareStudent(4, "Ana I", 1);
//	afiseazaStudent(s1);
//	Node* arbore = citireArboreStudentiDinFisier("studenti.txt");
//	printf("-----------------InOrdine----------------\n");
//	afiseazaArboreInOrdine(arbore);
//	/*printf("-----------------PostOrdine----------------\n");
//	afiseazaInPostordina(arbore);
//	printf("-----------------PreOrdine----------------\n");
//	afiseazaInPreordine(arbore);*/
//	printf("\nCautare student dupa id: ");
//	Student studentGasit = cautareStudentDupaId(arbore, 2);
//	afiseazaStudent(studentGasit);
//	free(studentGasit.nume);
//	dezalocareArbore(&arbore);
//	return 0;
//}