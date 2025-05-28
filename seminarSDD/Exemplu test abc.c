//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
////13
//struct Fotografie {
//	int id;
//	char* oras;
//	float rezolutie;
//};
//
//typedef struct Fotografie Fotografie;
//typedef struct Node Node;
//
//struct Node {
//	Fotografie info;
//	Node* st;
//	Node* dr;
//};
//
//Fotografie citireFotografieFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	char* aux;
//	Fotografie f;
//	fgets(buffer, 100, file);
//	aux = strtok(buffer, sep);
//	f.id = atoi(aux);
//	aux = strtok(NULL, sep);
//	f.oras = (char*)malloc(strlen(aux) + 1);
//	strcpy(f.oras, aux);
//	aux = strtok(NULL, sep);
//	f.rezolutie = atof(aux);
//	return f;
//}
//
//void afiseazaFoto(Fotografie f) {
//	printf("Id: %d\n", f.id);
//	printf("Oras: %s\n", f.oras);
//	printf("Rezolutie: %.2f\n\n", f.rezolutie);
//}
//
//void inserareNodInArbore(Node** rad, Fotografie f) {
//	if ((*rad) != NULL) {
//		if (f.id > (*rad)->info.id) {
//			 inserareNodInArbore(&((*rad)->dr), f);
//		}
//		else if (f.id < (*rad)->info.id) {
//			 inserareNodInArbore(&((*rad)->st),f);
//		}
//		else {
//			if ((*rad)->info.oras != NULL) {
//				free((*rad)->info.oras);
//			}
//			(*rad)->info.id = f.id;
//			(*rad)->info.oras = (char*)malloc(strlen(f.oras) + 1);
//			strcpy((*rad)->info.oras, f.oras);
//			(*rad)->info.rezolutie = f.rezolutie;
//		}
//	}
//	else {
//		(*rad) = malloc(sizeof(Node));
//		(*rad)->info = f;
//		(*rad)->info.oras = (char*)malloc(strlen(f.oras) + 1);
//		strcpy((*rad)->info.oras, f.oras);
//		(*rad)->st = NULL;
//		(*rad)->dr = NULL;
//	}
//}
//
//Node* citesteArboreDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	Node* rad = NULL;
//	while (!feof(file)) {
//		Fotografie f = citireFotografieFisier(file);
//		inserareNodInArbore(&rad, f);
//	}
//	fclose(file);
//	return rad;
//}
//
//
//void afisareArboreInOrdine(Node* rad) {
//	if (rad!=NULL) {
//		afisareArboreInOrdine(rad->st);
//		afiseazaFoto(rad->info);
//		afisareArboreInOrdine(rad->dr);
//	}
//}
//
//void dezalocareArbore(Node** rad) {
//	if ((*rad) != NULL) {
//		dezalocareArbore(&((*rad)->st));
//		dezalocareArbore(&((*rad)->dr));
//
//		free((*rad)->info.oras);
//		free((*rad));
//		*rad = NULL;
//
//	}
//}
//
//Fotografie getFotografieById(Node* rad, int idCautat) {
//	Fotografie f;
//	f.id = -1;
//	f.oras = NULL;
//	f.rezolutie = 0;
//	if (rad != NULL) {
//		if (rad->info.id == idCautat) {
//			f = rad->info;
//			f.oras = (char*)malloc(sizeof(strlen(rad->info.oras)));
//			strcpy(f.oras, rad->info.oras);
//		}
//		else if(rad->info.id > idCautat){
//			return getFotografieById(rad->st, idCautat);
//		}
//		else if (rad->info.id < idCautat) {
//			getFotografieById(rad->dr, idCautat);
//		}
//	}
//	return f;
//}
//
//int inaltimeArbore(Node* rad) {
//	if (rad) {
//		int nrSt = inaltimeArbore(rad->st);
//		int nrDr = inaltimeArbore(rad->dr);
//		return 1 + (nrSt > nrDr ? nrSt : nrDr);
//	}
//	return 0;
//}
//
//int nrNoduri(Node* rad) {
//	int nr = 0;
//	if (rad) {
//		nr += nrNoduri(rad->st);
//		nr += nrNoduri(rad->dr);
//		return 1 + nr;
//	}
//	return 0;
//}
//
////Node* stergereNodeDupaId(Node* rad, int idCautat) {
////	if (rad) {
////		if (rad->info.id > idCautat) {
////			rad->st = stergereNodeDupaId(rad->st, idCautat);
////		}else if (rad->info.id < idCautat) {
////			rad->dr = stergereNodeDupaId(rad->dr, idCautat);
////		}
////		else {
////			//niciun copil
////			if (rad->st == NULL && rad->dr == NULL) {
////				free(rad->info.oras);
////				free(rad);
////			}
////			//doar copil drept
////			else if (rad->st == NULL) {
////				Node* temp = rad->dr;
////				free(rad->info.oras);
////				free(rad);
////				return temp; 
////			}
////			else if (rad->dr == NULL) {
////				Node* temp = rad->st;
////				free(rad->info.oras);
////				free(rad);
////				return temp;
////			}
////			else {
////				//doi copii
////				//succeorul nodului sters va fi cel mai mic din arborele drept
////				Node* succesor = rad->dr;
////				while (succesor->st != NULL) {
////					succesor = succesor->st;
////				}
////				free(rad->info.oras);
////				rad->info.id = succesor->info.id;
////				rad->info.oras = (char*)malloc(strlen(succesor->info.oras) + 1);
////				strcpy(rad->info.oras, succesor->info.oras);
////				rad->info.rezolutie = succesor->info.rezolutie;
////
////				rad->dr = stergereNodeDupaId(rad->dr, succesor->info.id);
////			}
////			
////		}
////		return rad;
////	}
////	return rad;
////}
//
//int main() {
//	Node* arbore = citesteArboreDinFisier("fotografii.txt");
//	afisareArboreInOrdine(arbore);
//	Fotografie gasita = getFotografieById(arbore, 3);
//	printf("\nFOTOGRAFIE GASITA\n");
//	afiseazaFoto(gasita);
//	int inaltime = inaltimeArbore(arbore);
//	printf("Inaltime: %d", inaltime);
//
//	int nr = nrNoduri(arbore);
//	printf("Nr noduri: %d", nr);
//
//	arbore = stergereNodeDupaId(arbore, 11);
//	printf("\nNOD STERS DUPA ID\n");
//	afisareArboreInOrdine(arbore);
//
//	dezalocareArbore(&arbore);
//
//	return 0;
//}