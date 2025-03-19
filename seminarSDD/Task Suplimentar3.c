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
//void afisareVectorFilme(struct Film* filme, int nrFilme) {
//	for (int i = 0; i < nrFilme; i++) {
//		afisareFilm(filme[i]);
//		
//	}
//}
//
//struct Film citireFilm(FILE* file) {
//	struct Film f;
//	f.titlu = NULL;
//	f.nrActori = 0;
//	f.durata = 0;
//	f.nrRecenzii = 0;
//	f.note = NULL;
//
//	char buffer[100];
//	char sep[2] = ",\n";
//
//	if (fgets(buffer, sizeof(buffer), file) == NULL) {
//		return f; // Dacă nu mai sunt linii, returnăm un film "gol"
//	}
//
//	char* aux = strtok(buffer, sep);
//	if (aux == NULL) return f; // Verificăm dacă există titlul
//
//	f.titlu = (char*)malloc(strlen(aux) + 1);
//	if (f.titlu == NULL) {
//		printf("Eroare la alocarea memoriei pentru titlu!\n");
//		exit(1);
//	}
//	strcpy(f.titlu, aux);
//
//	char* token = strtok(NULL, sep);
//	if (token == NULL) return f;
//	f.nrActori = atoi(token);
//
//	token = strtok(NULL, sep);
//	if (token == NULL) return f;
//	f.durata = atof(token);
//
//	token = strtok(NULL, sep);
//	if (token == NULL) return f;
//	f.nrRecenzii = atoi(token);
//
//	if (f.nrRecenzii > 0) {
//		f.note = (float*)malloc(f.nrRecenzii * sizeof(float));
//		if (f.note == NULL) {
//			printf("Eroare la alocarea memoriei pentru note!\n");
//			exit(1);
//		}
//		for (int i = 0; i < f.nrRecenzii; i++) {
//			token = strtok(NULL, sep);
//			if (token == NULL) {
//				f.nrRecenzii = i;
//				break;
//			}
//			f.note[i] = atof(token);
//		}
//	}
//	else {
//		f.note = NULL;
//	}
//
//	return f;
//}
//
//void adaugaFilmInVector(struct Film** filme, int* nrFilme, struct Film f) {
//	struct Film* temp = (struct Film*)malloc((*nrFilme + 1) * sizeof(struct Film));
//	for (int i = 0; i < *nrFilme; i++) {
//		temp[i] = (*filme)[i];
//	}
//	temp[*nrFilme] = f;
//	(*nrFilme)++;
//	free(*filme);
//	*filme = temp;
//}
//
//
//struct Film* citireVectorFilme(const char* numeFisier, int* nrFilme) {
//	FILE* file = fopen(numeFisier, "r");
//	if (!file) {
//		printf("Eroare la deschiderea fisierului!\n");
//		return NULL;
//	}
//
//	struct Film* filme = NULL;
//	*nrFilme = 0;
//
//	while (1) {
//		struct Film f = citireFilm(file);
//		if (f.titlu == NULL) break; 
//
//		adaugaFilmInVector(&filme, nrFilme, f);
//	}
//
//	fclose(file);
//	return filme;
//}
//
//
//int main() {
//	int filme = 0;
//	struct Film* filmeVector = citireVectorFilme("filme.txt", &filme);
//	afisareVectorFilme(filmeVector, filme);
//	return 0;
//}