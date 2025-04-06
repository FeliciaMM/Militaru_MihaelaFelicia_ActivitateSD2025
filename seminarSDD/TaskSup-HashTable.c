#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Linear probing = "probam" fiecar epozitie in mod liniar
//Quadratic probing = ne mutam mai departe daca locul care este calculat
//Double hashing = calculam inca o data hash cu alta functie
//

struct Cladire {
    int id;
    int anConstructie;
    char* nume;
    int nrRenovari;
    int* anulRenovarii;
};

typedef struct Node Node;
typedef struct Cladire Cladire;

struct Node {
    Cladire info;
    Node* next;
};

struct HashTable {
    int dim;
    Node** tabela;
};

typedef struct HashTable HashTable;

Cladire citireCladireaDinFisier(FILE* file) {
    char buffer[100];
    char sep[3] = ",\n";
    fgets(buffer, 100, file);
    Cladire c;
    char* aux = strtok(buffer, sep);
    c.id = atoi(aux);

    aux = strtok(NULL, sep);
    c.anConstructie = atoi(aux);

    aux = strtok(NULL, sep);
    c.nume = malloc(strlen(aux) + 1); 
    strcpy(c.nume, aux);  

    aux = strtok(NULL, sep);
    c.nrRenovari = atoi(aux);

    c.anulRenovarii = NULL;
    if (c.nrRenovari > 0) {
        c.anulRenovarii = (int*)malloc(c.nrRenovari * sizeof(int));  
        for (int i = 0; i < c.nrRenovari; i++) {  
            aux = strtok(NULL, sep);
            c.anulRenovarii[i] = atoi(aux);
        }
    }

    return c;
}

void afisareCladire(Cladire cladire) {
    printf("Id: %d\n", cladire.id);
    printf("An Constructie: %d\n", cladire.anConstructie);
    printf("Numele cladirii: %s\n", cladire.nume);
    printf("Numar renovari: %d\n", cladire.nrRenovari);
    printf("Renovarile au avut loc in anii:\n ");
    for (int i = 0; i < cladire.nrRenovari; i++) {
        printf("%d", cladire.anulRenovarii[i]);
    }
}

void afisareLista(Node* cap) {
    while (cap!= NULL) {
        afisareCladire(cap->info);
        cap = cap->next;
    }
}

void adaugaCladiriInLista(Node* cap, Cladire cladireNoua) {
    Node* p = cap;
    while (p->next){
        p = p->next;
    }
    Node* nou = (Node*)malloc(sizeof(Node));
    nou->info = cladireNoua;
    nou->next = NULL;
    p->next = nou;
}

HashTable initializareHashTable(int dimensiune) {
    HashTable ht;
    ht.dim = dimensiune;
    ht.tabela = (Node**)malloc(dimensiune * sizeof(Node*));
    for (int i = 0; i < dimensiune; i++) {
        ht.tabela[i] = NULL;
    }
    return ht;
}

int functiaHash(int anulConstructiei,int dimensiune) {
    int suma = 0;
    while (anulConstructiei>0) {
        suma += anulConstructiei/10;
    }
    return suma % dimensiune;
}

void inserareCladireInTabela(HashTable hash, Cladire cladire) {
    int pozitie = functiaHash(cladire.nume, hash.dim);
}

HashTable citireCladiriDinFisier(const char* numeFisier, int dimesniune) {
    FILE* file = fopen(numeFisier, "r");
}



int main() {
    HashTable ht = initializareHashTable(7);
    /*Cladire c = citireCladireaDinFisier("cladiri.txt");*/
   

    return 0;
}
