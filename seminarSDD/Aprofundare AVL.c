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
//};
//
//typedef struct Student Student;
//typedef struct Node Node;
//
//struct Node {
//	Student info;
//	Node* st;
//	Node* dr;
//};
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
//int inaltimeArbore(Node* rad) {
//	if (rad) {
//		int inaltimeSt = inaltimeArbore(rad->st);
//		int inaltimeDr = inaltimeArbore(rad->dr);
//
//		return 1 + (inaltimeSt > inaltimeDr ? inaltimeSt : inaltimeDr);
//	}
//	return 0;
//
//}
//
//Node* rotireLaDreapta(Node* rad) {
//	if (rad) {
//		Node* aux = rad->st;
//		rad->st = aux->dr;
//		aux->dr = rad;
//		return aux;
//	}
//	return rad;
//}
//
//Node* rotireLaStanga(Node* rad) {
//	if (rad) {
//		Node* aux = rad->dr;
//		rad->dr = aux->st;
//		aux->st = rad;
//		return aux;
//	}
//	return rad;
//}
//
//int calculareGradEchilibru(Node* rad) {
//	if (rad) {
//		int inaltimeSt = inaltimeArbore(rad->st);
//		int inaltimeDr = inaltimeArbore(rad->dr);
//		return inaltimeSt - inaltimeDr;
//
//	}
//	else {
//		return 0;
//	}
//}
//
//Node* inserareStudentInAVL(Node* rad, Student s) {
//	if (rad) {
//		if (s.id < rad->info.id) {
//			rad->st = inserareStudentInAVL(rad->st, s);
//		}
//		else {
//			rad->dr = inserareStudentInAVL(rad->dr, s);
//		}
//		if (calculareGradEchilibru(rad) == 2) {
//			if (calculareGradEchilibru(rad->st) != 1) {
//				rad->st = rotireLaStanga(rad->st);
//			}
//			rad = rotireLaDreapta(rad);
//		}
//		if (calculareGradEchilibru(rad) == -2) {
//			if (calculareGradEchilibru(rad->dr) != -1) {
//				rad->dr = rotireLaDreapta(rad->dr);
//			}
//			rad = rotireLaStanga(rad);
//		}
//
//		return rad;
//	}
//	else {
//		Node* nou = (Node*)malloc(sizeof(Node));
//		nou->dr = NULL;
//		nou->st = NULL;
//		nou->info = s;
//		return nou;
//	}
//}
//
//
//
//Node* citireArboreDinFisier(const char* numeFisier) {
//	Node* rad = NULL;
//	FILE* file = fopen(numeFisier, "r");
//	while (!feof(file)) {
//		rad = inserareStudentInAVL(rad, citireStudentFisier(file));
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
//
//int main() {
//	Node* rad = citireArboreDinFisier("studenti.txt");
//	afisareArboreInPreordine(rad);
//	return 0;
//}