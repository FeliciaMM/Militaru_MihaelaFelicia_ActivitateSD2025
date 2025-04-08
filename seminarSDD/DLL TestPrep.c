//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct Film {
//	int id;
//	char* titlu;
//	int nrActori;
//	float durata;
//	int nrRecenzii;
//	float* note;
//};
//
//typedef struct Film Film;
//typedef struct Node Node;
//typedef struct List List;
//
//struct Node {
//	Film info;
//	Node* next;
//	Node* prev;
//};
//
//struct List {
//	Node* first;
//	Node* last;
//	int nrNoduri;
//};
//
//
//Film citireTablouDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	Film f;
//	if (fgets(buffer, 100, file)) {
//		char* aux = strtok(buffer, sep);
//		if (!aux) return f;
//		f.id = atoi(aux);
//		aux = strtok(NULL, sep);
//		f.titlu = (char*)malloc(strlen(aux) + 1);
//		strcpy(f.titlu, aux);
//		aux = strtok(NULL, sep);
//		f.nrActori = atoi(aux);
//		aux = strtok(NULL, sep);
//		f.durata = atof(aux);
//		aux = strtok(NULL, sep);
//		f.nrRecenzii = atoi(aux);
//		f.note = NULL;
//		if (f.nrRecenzii > 0) {
//			f.note = (float*)malloc(f.nrRecenzii * sizeof(float));
//			for (int i = 0; i < f.nrRecenzii; i++) {
//				aux = strtok(NULL, sep);
//				if (aux) {
//					f.note[i] = atof(aux);
//				}
//				else {
//					f.note[i] = 0;
//				}
//
//			}
//		}
//
//
//	}
//	return f;
//}
//
//void afisareFilm(Film film) {
//	    printf("\nId: %d\n", film.id);
//	    printf("Titlu: %s\n", film.titlu);
//	    printf("Numar actori: %d\n", film.nrActori);
//	    printf("Durata: %.2f\n", film.durata);
//	    printf("Numar recenzii: %d\n", film.nrRecenzii);
//	    if (film.nrRecenzii > 0) {
//	        printf("Note din recenzii: ");
//	        for (int i = 0; i < film.nrRecenzii; i++) {
//	            printf("%.2f ", film.note[i]);
//	        }
//	        printf("\n");
//	    }
//	    else {
//	        printf("Nu exista recenzii disponibile.\n");
//	    }
//	}
//
//void afisareListaInceput(List list) {
//	Node* temp = list.first;
//	while (temp) {
//		afisareFilm(temp->info);
//		temp = temp->next;
//	}
//}
//
//void afisareListaFinal(List list) {
//	Node* temp = list.last;
//	while (temp) {
//		afisareFilm(temp->info);
//		temp = temp->prev;
//	}
//}
//
//void adaugaFilmInListaLaFinal(List* list, Film filmNou) {
//	Node* nou = (Node*)malloc(sizeof(Node));
//	nou->info = filmNou;
//	nou->next = NULL;
//	nou->prev = list->last;
//	if (list->last != NULL) {
//		list->last->next = nou;
//	}
//	else {
//		list->first = nou;
//	}
//	list->last = nou;
//	list->nrNoduri++;
//}
//
//void adaugaNodLaInceput(List* list, Film filmNou) {
//	Node* nou = (Node*)malloc(sizeof(Node));
//	nou->info = filmNou;
//	nou->prev = NULL;
//	nou->next = list->first;
//	if (list->first!=NULL) {
//		list->first->prev = nou;
//	}else {
//		list->last = nou;
//	}
//	list->first = nou;
//	list->nrNoduri++;
//}
//
//List citireListaDublaDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	List list;
//	list.first = NULL;
//	list.last = NULL;
//	list.nrNoduri = 0;   
//	while (!feof(f)) {
//		adaugaFilmInListaLaFinal(&list, citireTablouDinFisier(f));
//	}
//	fclose(f);
//	return list;
//}
//
//void dezalocare(List* lista) {
//	Node* temp = lista->first;
//	while (temp) {
//		Node* aux = temp;
//		temp = temp->next;
//		if (aux->info.titlu) {
//			free(aux->info.titlu);
//		}
//		if (aux->info.note) {
//			free(aux->info.note);
//		}
//		free(aux);
//	}
//	lista->first = NULL;
//	lista->last = NULL;
//	lista->nrNoduri = 0;
//}
//
//float calculeazaDurataMedie(List list) {
//	if (list.nrNoduri > 0) {
//		float suma = 0;
//		int counter = 0;
//		Node* p = list.first;
//		while (p) {
//			suma += p->info.durata;
//			counter++;
//			p = p->next;
//		}
//		return suma / list.nrNoduri;
//	}
//	
//	return 0;
//}
//
//void stergeFilmDupaId(List* list, int idSters) {
//	if (list->first == NULL) {
//		return;
//	}
//		Node* p = list->first;
//		while (p!=NULL && p->info.id!=idSters) {
//			p = p->next;
//		}
//		if (p == NULL) {
//			return;
//		}
//		//Daca p este primul
//		if (p->prev == NULL) {
//			list->first = p->next;
//			if (list->first) {
//				list->first->prev = NULL;
//			}
//		}
//		else {
//			p->prev->next = p->next;
//			
//		}if (p->next) {
//			p->next->prev = p->prev;
//		}else{
//			list->last = p->prev;
//		}
//		if (p->info.titlu) {
//			free(p->info.titlu);
//		}
//		if (p->info.note) {
//			free(p->info.note);
//		}
//		free(p);
//		list->nrNoduri--;
//	
//}
//
//char* getNumeFilmMultiActori(List list) {
//	int nrMaxActori = 0;
//	char* numeMax="";
//	Node* temp = list.first;
//	while (temp) {
//		if (temp->info.nrActori > nrMaxActori) {
//			nrMaxActori = temp->info.nrActori;
//			numeMax = temp->info.titlu;
//		}
//		temp = temp->next;
//	}
//	return numeMax;
//}
//
//int main() {
//	List list = citireListaDublaDinFisier("filme.txt");
//	afisareListaInceput(list);
//	printf("\nMedia duratei: %.2f", calculeazaDurataMedie(list));
//	printf("\n Lista dupa stergere: ");
//	stergeFilmDupaId(&list, 10);
//	afisareListaFinal(list);
//	printf("Numele filmului cu ci mai multi actori: %s", getNumeFilmMultiActori(list));
//
//	dezalocare(&list);
//	return 0;
//}