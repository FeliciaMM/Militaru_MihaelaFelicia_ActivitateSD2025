//Felicia Militaru => Film
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

struct Film citireDeLaTastatura() {
	struct Film film;
	char buffer[100];

	printf("Introduceti titlul filmului: ");
	scanf(" %99[^\n]", buffer);
	film.titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(film.titlu, buffer);
	printf("Introduceti numarul de actori: ");
	scanf("%d", &film.nrActori);
	printf("Introduceti durata filmului (minute): ");
	scanf("%f", &film.durata);
	printf("Introduceti numarul de recenzii: ");	
	scanf("%d", &film.nrRecenzii);
	film.note = (float*)malloc(film.nrRecenzii * sizeof(float));
	printf("Introduceti notele primite de film in recenzii: \n");
	for (int i = 0; i < film.nrRecenzii; i++) {
		scanf("%f", &film.note[i]);
	}
	return film;

}


float mediaNotelor(int nrRecenzii, float* note) {
	if (nrRecenzii == 0) return 0;
	int medie = 0;
	for (int i = 0; i < nrRecenzii; i++) {
		medie += note[i];
	}
	medie = medie / (float)nrRecenzii;
	return medie;
}

void modificaDurata(struct Film* film, float nouaDurata) {
	film->durata = nouaDurata;
	printf("Durata filmului a fost modificata cu succes la %.2f\n",nouaDurata);
}

void afisareFilm(struct Film film) {
	printf("\nTitlu: %s\n", film.titlu);
	printf("Numar actori: %d\n", film.nrActori);	
	printf("Durata: %.2f\n", film.durata);
	printf("Numar recenzii: %d\n", film.nrRecenzii);
	if (film.nrRecenzii > 0) {
		printf("Note din recenzii: ");
		for(int i =0; i< film.nrRecenzii; i++) {
			printf("%.2f ", film.note[i]);
		}
		printf("\n");
	}
	else {
		printf("Nu exista recenzii disponibile.");
	
	}
	
	
}


int main() {
	struct Film film = citireDeLaTastatura();
	float medie = mediaNotelor(film.nrRecenzii, film.note);
	printf("\nMedia notelor filmului \"%s\" este: %.2f\n", film.titlu, medie);
	modificaDurata(&film, 120);
	afisareFilm(film);
}