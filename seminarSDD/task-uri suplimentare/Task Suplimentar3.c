﻿//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct Film {
//    int id;
//    char* titlu;
//    int nrActori;
//    float durata;
//    int nrRecenzii;
//    float* note;
//};
//
//typedef struct Film Film;
//
//void afisareFilm(Film film) {
//    printf("Id: %d\n", film.id);
//    printf("Titlu: %s\n", film.titlu);
//    printf("Numar actori: %d\n", film.nrActori);
//    printf("Durata: %.2f\n", film.durata);
//    printf("Numar recenzii: %d\n", film.nrRecenzii);
//    if (film.nrRecenzii > 0) {
//        printf("Note din recenzii: ");
//        for (int i = 0; i < film.nrRecenzii; i++) {
//            printf("%.2f ", film.note[i]);
//        }
//        printf("\n");
//    }
//    else {
//        printf("Nu exista recenzii disponibile.\n");
//    }
//}
//
//void afisareVectorFilme(Film* filme, int nrFilme) {
//    for (int i = 0; i < nrFilme; i++) {
//        afisareFilm(filme[i]);
//    }
//}
//
//void adaugareFilmInVector(Film** filme, int* nrFilme, Film filmNou) {
//    Film* aux = (Film*)malloc(sizeof(Film) * ((*nrFilme) + 1));
//    if (*filme) {
//        for (int i = 0; i < *nrFilme; i++) {
//            aux[i] = (*filme)[i];
//        }
//        free(*filme);
//    }
//    aux[*nrFilme] = filmNou;
//    *filme = aux;
//    (*nrFilme)++;
//}
//
//Film citireFilm(FILE* file) {
//    char buffer[100];
//    char sep[] = ",\n";
//    char* aux;
//
//    if (!fgets(buffer, sizeof(buffer), file)) {
//        return (Film) { 0 };
//    }
//
//    Film f;
//
//    aux = strtok(buffer, sep);
//    f.id = atoi(aux);
//
//    aux = strtok(NULL, sep);
//    f.titlu = malloc(strlen(aux) + 1);
//    if (f.titlu) strcpy(f.titlu, aux);
//
//
//    aux = strtok(NULL, sep);
//    f.nrActori = atoi(aux);
//
//    aux = strtok(NULL, sep);
//    f.durata = atof(aux);
//
//    aux = strtok(NULL, sep);
//
//    f.nrRecenzii = atoi(aux);
//
//    
//
//    f.note = NULL;
//    if (f.nrRecenzii > 0) {
//        f.note = (float*)malloc(f.nrRecenzii * sizeof(float));
//        if (f.note) {
//            for (int i = 0; i < f.nrRecenzii; i++) {
//                aux = strtok(NULL, sep);
//                f.note[i] = atof(aux);
//            }
//        }
//    }
//
//    return f;
//}
//
//void salvareInFisier(Film film, const char* numeFisierSalvare) {
//    FILE* file = fopen(numeFisierSalvare, "a");
//    fprintf(file,"%d, %s, %d, %.2f, %d",film.id, film.titlu, film.nrActori, film.durata, film.nrRecenzii);
//    for(int i = 0; i< film.nrRecenzii; i++){
//		fprintf(file, ", %.2f", film.note[i]);
//	}
//    fprintf(file, "\n");
//	fclose(file);
//}
//
//Film* citireVectorFilme(const char* numeFisier, int* nrFilmeCitite) {
//    FILE* file = fopen(numeFisier, "r");
//    if (!file) {
//        printf("Eroare la deschiderea fisierului!\n");
//        return NULL;
//    }
//
//    Film* filme = NULL;
//    Film temp;
//    while ((temp = citireFilm(file)).titlu != NULL) {
//        adaugareFilmInVector(&filme, nrFilmeCitite, temp);
//    }
//
//    fclose(file);
//    return filme;
//}
//
//void salvareVectorFilmeInFisier(Film* filme, int nrFilme, const char* numeFisierVector) {
//    FILE* file = fopen(numeFisierVector, "w");
//    for (int i = 0; i < nrFilme; i++) {
//        fprintf(file, "%d, %s, %d, %.2f, %d", filme[i].id, filme[i].titlu, filme[i].nrActori, filme[i].durata, filme[i].nrRecenzii);
//        for (int j = 0; j < filme[i].nrRecenzii; j++) {
//            fprintf(file, ", %.2f", filme[i].note[j]);
//        }
//        fprintf(file, "\n");
//    }
//    fclose(file);
//}
//
//void dezalocareVector(Film** vector, int* nrFilme) {
//    for (int i = 0; i < *nrFilme; i++) {
//        free((*vector)[i].titlu);
//        free((*vector)[i].note);
//    }
//    free(*vector);
//    *vector = NULL;
//    *nrFilme = 0;
//}
//
//int main() {
//    int nrFilme = 0;
//    Film* filme = citireVectorFilme("filme.txt", &nrFilme);
//    salvareInFisier(filme[0], "filmeSalvate.txt");
//    salvareVectorFilmeInFisier(filme, 4, "filmeSalvateVector.txt");
//
//
//    if (filme) {
//        afisareVectorFilme(filme, nrFilme);
//        dezalocareVector(&filme, &nrFilme);
//    }
//
//    return 0;
//}
