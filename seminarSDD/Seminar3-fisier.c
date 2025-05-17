//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//    int id;
//    int nrUsi;
//    float pret;
//    char* model;
//    char* numeSofer;
//    unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//void afisareMasina(Masina masina) {
//    printf("\nID: %d\n", masina.id);
//    printf("nrUsi: %d\n", masina.nrUsi);
//    printf("pret: %.2f\n", masina.pret);
//    printf("model: %s\n", masina.model);
//    printf("numeSofer: %s\n", masina.numeSofer);
//    printf("serie: %c\n", masina.serie);
//}
//
//void afisareVectorMasini(Masina* masini, int nrMasini) {
//    for (int i = 0; i < nrMasini; i++) {
//        afisareMasina(masini[i]);
//    }
//}
//
//void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
//    Masina* aux = (Masina*)malloc((*nrMasini + 1) * sizeof(Masina));
//    if (!aux) {
//        printf("Eroare la alocarea memoriei!\n");
//        return;
//    }
//
//    for (int i = 0; i < *nrMasini; i++) {
//        aux[i] = (*masini)[i];  // Copiere structuri
//    }
//
//    aux[*nrMasini] = masinaNoua;  // Adăugare nouă mașină
//    (*nrMasini)++;
//    free(*masini);
//    *masini = aux;
//}
//
//Masina citireMasinaFisier(FILE* file) {
//    char buffer[100];
//    char sep[3] = ",\n";
//    char* aux;
//
//    if (!fgets(buffer, 100, file)) {
//        Masina m = { 0 };
//        return m;
//    }
//
//    Masina m;
//    aux = strtok(buffer, sep);
//    m.id = atoi(aux);
//    m.nrUsi = atoi(strtok(NULL, sep));
//    m.pret = atof(strtok(NULL, sep));
//
//
//    aux = strtok(NULL, sep);
//    m.model = malloc(strlen(aux) + 1);
//    if (m.model) strcpy(m.model, aux);
//
//    aux = strtok(NULL, sep);
//    m.numeSofer = malloc(strlen(aux) + 1);
//    if (m.numeSofer) strcpy(m.numeSofer, aux);
//
//    m.serie = strtok(NULL, sep)[0];
//
//    return m;
//}
//
//Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
//    FILE* file = fopen(numeFisier, "r");
//    if (!file) {
//        printf("Eroare la deschiderea fisierului!\n");
//        return NULL;
//    }
//
//    Masina* masini = NULL;
//    Masina masinaNoua;
//    while (!feof(file)) {
//        masinaNoua = citireMasinaFisier(file);
//        if (masinaNoua.model != NULL && masinaNoua.numeSofer != NULL) {
//            adaugaMasinaInVector(&masini, nrMasiniCitite, masinaNoua);
//        }
//    }
//
//    fclose(file);
//    return masini;
//}
//
//void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
//    for (int i = 0; i < *nrMasini; i++) {
//        free((*vector)[i].model);
//        free((*vector)[i].numeSofer);
//    }
//    free(*vector);
//    *vector = NULL;
//    *nrMasini = 0;
//}
//
//float pretMediuDupaNrUsi(Masina* vector, int nrMasini, int nrUsi) {
//    float suma = 0;
//    int index = 0;
//    for (int i = 0; i < nrMasini; i++) {
//        if (vector[i].nrUsi == nrUsi) {
//            suma += vector[i].pret;
//            index++;
//        }
//    }
//    if (index > 0) {
//        return suma / index;
//    }
//    else return 0;
//}
//
//int main() {
//    Masina* masini = NULL;
//    int nrMasini = 0;
//    masini = citireVectorMasiniFisier("masini.txt", &nrMasini);
//
//    if (masini) {
//        afisareVectorMasini(masini, nrMasini);
//        dezalocareVectorMasini(&masini, &nrMasini);
//    }
//
//    float medie = pretMediuDupaNrUsi(masini, nrMasini, 4);
//    printf("Meida masinilor cu 5 usi %d", medie);
//    dezalocareVectorMasini(&masini, &nrMasini);
//
//    return 0;
//}
