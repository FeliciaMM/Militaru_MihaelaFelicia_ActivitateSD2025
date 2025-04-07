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
    printf("\nId: %d\n", cladire.id);
    printf("An Constructie: %d\n", cladire.anConstructie);
    printf("Numele cladirii: %s\n", cladire.nume);
    printf("Numar renovari: %d\n", cladire.nrRenovari);
    printf("Renovarile au avut loc in anii:\n ");
    for (int i = 0; i < cladire.nrRenovari; i++) {
        printf("%d\n", cladire.anulRenovarii[i]);
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
    return anulConstructiei % dimensiune;
}

void inserareCladireInTabela(HashTable hash, Cladire cladire) {
    int pozitie = functiaHash(cladire.nume, hash.dim);
    if (hash.tabela[pozitie] == NULL) {
        hash.tabela[pozitie] = (Node*)malloc(sizeof(Node));
        hash.tabela[pozitie]->info = cladire;
        hash.tabela[pozitie]->next = NULL;
    }
    else {
        adaugaCladiriInLista(hash.tabela[pozitie], cladire);
    }
}

HashTable citireCladiriDinFisier(const char* numeFisier,int dimesniune) {
    HashTable hash = initializareHashTable(dimesniune);
    FILE* file = fopen(numeFisier, "r");
    while (!feof(file)) {
        Cladire cladire = citireCladireaDinFisier(file);
        inserareCladireInTabela(hash, cladire);
    }
    fclose(file);
    return hash;
}

void afisareTabelaMasini(HashTable ht) {
    for (int i = 0; i < ht.dim; i++) {
        if (ht.tabela[i] != NULL) {
            printf("Masinile de pe pozitia %d sunt:\n", i);
            afisareLista(ht.tabela[i]);
        }else{
            printf("\nPe poz %d nu avem masini",i);
        }
    }
}

void dezalocareLista(Node** cap) {
    Node* p = *cap;
    while (p) {
        Node* temp = p;
        p = p->next;
        if (temp->info.nume) {
            free(temp->info.nume);
        }
        if (temp->info.anulRenovarii) {
            free(temp->info.anulRenovarii);
        }
        free(temp);
    }
    *cap = NULL;
}

void dezalocare(HashTable *ht) {
    for (int i = 0; i < ht->dim; i++) {
        dezalocareLista(&(ht->tabela[i]));
    }
    free(ht->tabela);
    ht->tabela = NULL;
    ht->dim = 0;
}



int main(){
    HashTable ht = citireCladiriDinFisier("cladiri.txt",7);
    afisareTabelaMasini(ht);
    int anCluster = 1999;
    printf("\nClusterul cladirilor construite in anul %d: \n", anCluster);
    dezalocare(&ht);
    return 0;
}
