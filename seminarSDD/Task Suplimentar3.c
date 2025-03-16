#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>


struct Film {
	char* titlu;
	int nrActori;
	float durata;
	int nrRecenzii;
	float* note;
};

struct Film initializare(char* titlu, int nrActori, float durata, int nrRecenzii, float* note) {
	struct Film f;
	f.titlu = (char*)malloc((strlen(titlu) + 1) * sizeof(char));
	strcpy(f.titlu, titlu);
	f.nrActori = nrActori;
	f.durata = durata;
	f.nrRecenzii = nrRecenzii;
	f.note = (float*)malloc(nrRecenzii * sizeof(float));
	for (int i = 0; i < nrRecenzii; i++) {
		f.note[i] = note[i];
	}
	return f;
}

void afisareFilm(struct Film film) {
	printf("\nTitlu: %s\n", film.titlu);
	printf("Numar actori: %d\n", film.nrActori);
	printf("Durata: %.2f\n", film.durata);
	printf("Numar recenzii: %d\n", film.nrRecenzii);
	if (film.nrRecenzii > 0) {
		printf("Note din recenzii: ");
		for (int i = 0; i < film.nrRecenzii; i++) {
			printf("%.2f ", film.note[i]);
		}
		printf("\n");
	}
	else {
		printf("Nu exista recenzii disponibile.");
	}
}

