//#define _CRT_SECURE_NO_WARNINGS
//#include <stdlib.h>
//#include <stdio.h>
//
//
//struct Film {
//	char* titlu;
//	int nrActori;
//	float durata;
//	int nrRecenzii;
//	float* note;
//};
//
//struct Film initializare(char* titlu, int nrActori, float durata, int nrRecenzii, float* note) {
//	struct Film f;
//	f.titlu = (char*)malloc((strlen(titlu) + 1) * sizeof(char));
//	strcpy(f.titlu, titlu);
//	f.nrActori = nrActori;
//	f.durata = durata;
//	f.nrRecenzii = nrRecenzii;
//	f.note = (float*)malloc(nrRecenzii * sizeof(float));
//	for (int i = 0; i < nrRecenzii; i++) {
//		f.note[i] = note[i];
//	}
//	return f;
//}
//
//void afisareFilm(struct Film film) {
//	printf("\nTitlu: %s\n", film.titlu);
//	printf("Numar actori: %d\n", film.nrActori);
//	printf("Durata: %.2f\n", film.durata);
//	printf("Numar recenzii: %d\n", film.nrRecenzii);
//	if (film.nrRecenzii > 0) {
//		printf("Note din recenzii: ");
//		for (int i = 0; i < film.nrRecenzii; i++) {
//			printf("%.2f ", film.note[i]);
//		}
//		printf("\n");
//	}
//	else {
//		printf("Nu exista recenzii disponibile.");
//	}
//}
//
//float mediaNotelor(int nrRecenzii, float* note) {
//	if (nrRecenzii == 0) return 0;
//	int medie = 0;
//	for (int i = 0; i < nrRecenzii; i++) {
//		medie += note[i];
//	}
//	medie = medie / (float)nrRecenzii;
//	return medie;
//}
//
//
//void afisareVector(struct Film* filme, int nrFilme) {
//	for (int i = 0; i < nrFilme; i++) {
//		afisareFilm(filme[i]);
//	}
//}
//
//
//void copiazaFilmeMediaMare(struct Film* vector,int nrFilme, float medieMin, struct Film** vectorNou, int* dimesniune) {
//	*dimesniune = 0;
//	for(int i =0; i< nrFilme; i++) {
//		if(mediaNotelor(vector[i].nrRecenzii, vector[i].note) > medieMin) {
//			(*dimesniune)++;
//			
//		}
//	}
//	*vectorNou = (struct Film*)malloc(*vectorNou, *dimesniune * sizeof(struct Film));
//	int k = 0;
//	for(int i =0; i< nrFilme; i++) {
//		if(mediaNotelor(vector[i].nrRecenzii, vector[i].note) > medieMin) {
//			(*vectorNou)[k] = vector[i];
//			k++;
//		}
//	}
//}
//
//
//void mutaFilmeDurataMare(struct Film** vector, int* nrFilme, float durataMin, struct Film** vectorNou, int* dimensiuneNoua) {	*dimensiuneNoua = 0;
//	*vectorNou = NULL;
//
//	for (int i = 0; i < *nrFilme; i++) {
//		if ((*vector)[i].durata > durataMin) {
//			(*dimensiuneNoua)++;
//			struct Film* temp = (struct Film*)realloc(*vectorNou, (*dimensiuneNoua) * sizeof(struct Film));
//			*vectorNou = temp;
//			(*vectorNou)[*dimensiuneNoua - 1] = (*vector)[i];
//
//			for (int j = i; j < *nrFilme - 1; j++) {
//				(*vector)[j] = (*vector)[j + 1];
//			}
//			(*nrFilme)--;
//			i--;
//		}
//	}
//}
//
//struct Film* concateneazaVectori(struct Film* v1, int n1, struct Film* v2, int n2, int* dimensiuneNoua) {
//	*dimensiuneNoua = n1 + n2;
//	struct Film* rezultat = (struct Film*)malloc((*dimensiuneNoua) * sizeof(struct Film));
//
//	for (int i = 0; i < n1; i++) {
//		rezultat[i] = initializare(v1[i].titlu, v1[i].nrActori, v1[i].durata, v1[i].nrRecenzii, v1[i].note);
//	}
//	for (int i = 0; i < n2; i++) {
//		rezultat[n1 + i] = initializare(v2[i].titlu, v2[i].nrActori, v2[i].durata, v2[i].nrRecenzii, v2[i].note);
//	}
//
//	return rezultat;
//}
//
//
//int main() {
//	struct Film* filme = NULL;
//	int nrFilme = 5;
//	filme = (struct Film*)malloc(nrFilme * sizeof(struct Film));
//	filme[0] = initializare("Titanic", 5, 180, 3, (float[]){ 8.5, 9.0, 7.5 });
//	filme[1] = initializare("Somwhere in time", 4, 120, 4, (float[]) { 7, 6.5, 8.5, 7 });
//	filme[2] = initializare("It", 7, 150, 2, (float[]) { 9.5,9 });
//	filme[3] = initializare("Spider-Man",5, 135, 3, (float[]) { 7, 6.5, 8.5 });
//	filme[4] = initializare("Morbius", 3, 95, 3, (float[]) { 5, 6.5, 4});
//
//	afisareVector(filme, nrFilme);
//
//	//copiaza filme cu medie peste 8
//	struct Film* filmeMedieMare = NULL;
//	int nrFilmeMedieMare = 0;
//	copiazaFilmeMediaMare(filme, nrFilme, 7, &filmeMedieMare, &nrFilmeMedieMare);
//	
//	printf("\nUrmatoarele filme au o medie peste nota 7: \n");
//	afisareVector(filmeMedieMare, nrFilmeMedieMare);
//
//
//	struct Film* filmeDurataMare = NULL;
//	int nrFilmeDurataMare = 0;
//	mutaFilmeDurataMare(&filme, &nrFilme, 120, &filmeDurataMare, &nrFilmeDurataMare);
//
//	printf("\nFilmele mutate cu durata peste 120 minute:\n");
//	afisareVector(filmeDurataMare, nrFilmeDurataMare);
//
//	int nrFilmeConcatenate = 0;
//	struct Film* filmeConcatenate = concateneazaVectori(filmeMedieMare, nrFilmeMedieMare, filmeDurataMare, nrFilmeDurataMare, &nrFilmeConcatenate);
//
//	printf("\nVectorul concatenat de filme:\n");
//	afisareVector(filmeConcatenate, nrFilmeConcatenate);
//
//}