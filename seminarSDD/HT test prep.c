////NU FACEM CU TABLOURI CA E CURSED
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct Cladire {
//	int id;
//    int anConstructie;
//    char* nume;
//    int nrRenovari;
//    int* anulRenovarii;
//};
//
//typedef struct Cladire Cladire;
//typedef struct Node Node;
//typedef struct HashTable HashTable;
//
//struct Node {
//    Cladire info;
//    Node* next;
//};
//
//struct HashTable {
//    int dim;
//    Node** tabela;
//};
//
//Cladire citireCladireDinFisier(FILE* file) {
//    char buffer[100];
//    char sep[3] = ",\n";
//    char* aux;
//    Cladire c;
//    if (fgets(buffer, 100, file)) {
//        aux = strtok(buffer, sep);
//        if (!aux)return c;
//        c.id = atoi(aux);
//        aux = strtok(NULL, sep);
//        c.anConstructie = atoi(aux);
//        aux = strtok(NULL, sep);
//        c.nume = (char*)malloc(strlen(aux) + 1);
//        strcpy(c.nume, aux);
//        aux = strtok(NULL, sep);
//        c.nrRenovari = atoi(aux);
//        c.anulRenovarii = NULL;
//        if (c.nrRenovari > 0) {
//            c.anulRenovarii = (int*)malloc(c.nrRenovari * sizeof(int));
//            for (int i = 0; i < c.nrRenovari; i++) {
//                aux = strtok(NULL, sep);
//                if (aux) {
//                    c.anulRenovarii[i] = atoi(aux);
//                }
//                else {
//                    c.anulRenovarii[i] = 0;
//                }
//                
//            }
//        }
//    }
//    return c;
//}
//
//void afisareCladire(Cladire cladire) {
//    printf("\nId: %d\n", cladire.id);
//    printf("An Constructie: %d\n", cladire.anConstructie);
//    printf("Numele cladirii: %s\n", cladire.nume);
//    printf("Numar renovari: %d\n", cladire.nrRenovari);
//    printf("Renovarile au avut loc in anii:\n ");
//    for (int i = 0; i < cladire.nrRenovari; i++) {
//        printf("%d\n", cladire.anulRenovarii[i]);
//    }
//}
//
//void afisareListCladiri(Node* cap) {
//    while (cap) {
//        afisareCladire(cap->info);
//        cap = cap->next;
//    }
//}
//
//void adaugareCladiriInLista(Node** cap, Cladire cladireNoua) {
//    Node* nou = (Node*)malloc(sizeof(Node));
//    nou->info = cladireNoua;
//    nou->next = *cap;
//    *cap = nou;
//}
//
//HashTable initalizareHashTable( int dimensiune) {
//    HashTable ht;
//    ht.dim = dimensiune;
//    ht.tabela = (Node**)malloc(dimensiune*sizeof(Node*));
//    for (int i = 0; i < ht.dim; i++) {
//        ht.tabela[i] = NULL;
//    }
//    return ht;
//
//}
//
//int functiaHash(int anConstructie, int dim) {
//    return anConstructie % dim;
//    
//}
//
//void inserareInTabela(HashTable hash, Cladire cladire) {
//  int pozitie = functiaHash(cladire.anConstructie, hash.dim);
//    if (hash.tabela[pozitie] == NULL) {
//        hash.tabela[pozitie] = (Node*)malloc(sizeof(Node));
//        hash.tabela[pozitie]->info = cladire;
//        hash.tabela[pozitie]->next = NULL;
//    }
//    else {
//        adaugareCladiriInLista(&hash.tabela[pozitie], cladire);
//    }
//}
//
//HashTable citireCladiriDinFisier(const char* numeFisier, int dimensiune) {
//    HashTable hash = initalizareHashTable(dimensiune);
//    FILE* f = fopen(numeFisier, "r");
//    if (f) {
//        while (!feof(f)){
//            Cladire c = citireCladireDinFisier(f);
//            inserareInTabela(hash, c);
//        }
//    }
//    fclose(f);
//    return hash;
//}
//
//void afisareTabela(HashTable hash) {
//    for (int i = 0; i < hash.dim; i++) {
//        if (hash.tabela[i] != NULL) {
//            printf("Clusterul %d: ", i);
//            afisareListCladiri(hash.tabela[i]);
//        }
//        else {
//            printf("\nPe poz %d nu avem masini", i);
//        }
//    }
//}
//
//void dezalocareLista(Node** cap) {
//    Node* p = *cap;
//    while (p) {
//        Node* temp = p;
//        p = p->next;
//        if (temp->info.nume) {
//            free(temp->info.nume);
//        }
//        if (temp->info.anulRenovarii) {
//            free(temp->info.anulRenovarii);
//        }
//        free(temp);
//    }
//    *cap = NULL;
//}
//
//void dezalocareTabela(HashTable *ht) {
//    for (int i = 0; i < ht->dim; i++) {
//        dezalocareLista(&(ht->tabela[i]));
//     
//    }
//    free(ht->tabela);
//    ht->tabela = NULL;
//    ht->dim = 0;
// 
//}
//
//float calculeazMedieLista(Node* cap) {
//    float suma = 0;
//    int counter = 0;
//    while (cap) {
//        suma += cap->info.anConstructie;
//        counter++;
//        cap = cap->next;
//
//    }
//    return suma / counter;
//}
//
//float* anMediuConstructieCluster(HashTable ht, int *nrClustere) {
//    float* preturi = NULL;
//    *nrClustere = 0;
//    
//    for (int i = 0; i < ht.dim; i++) {
//        if (ht.tabela[i] != NULL) {
//            (*nrClustere)++;
//        }
//   }
//    preturi = (float*)malloc(sizeof(float) + (*nrClustere));
//    int contor = 0;
//    for (int i = 0; i < ht.dim; i++) {
//        if (ht.tabela[i] != NULL) {
//            preturi[contor] = calculeazMedieLista(ht.tabela[i]);
//            contor++;
//        }
//    }
//    return preturi;
//}
//
//Cladire cautareInLista(Node *cap, int anCautat) {
//    Cladire c;
//    c.id = -1;
//    while (cap && cap->info.anConstructie != anCautat) {
//        cap = cap->next;
//    }
//    if (cap) {
//        c.id = cap->info.id;
//        c.anConstructie = cap->info.anConstructie;
//        c.nrRenovari = cap->info.nrRenovari;
//
//        c.nume = (char*)malloc(strlen(cap->info.nume) + 1);
//        strcpy(c.nume, cap->info.nume);
//
//        if (c.nrRenovari > 0 && cap->info.anulRenovarii != NULL) {
//            c.anulRenovarii = (int*)malloc(sizeof(int) * c.nrRenovari);
//            for (int i = 0; i < c.nrRenovari; i++) {
//                c.anulRenovarii[i] = cap->info.anulRenovarii[i];
//            }
//        }
//    }
//    return c;
//}
//
//
//Cladire getCladireDupaAnConstructie(HashTable ht, int anCautat) {
//    Cladire c;
//    c.id = -1;
//    int pozitie = functiaHash(anCautat, ht.dim);
//    if (pozitie >= 0 && pozitie < ht.dim) {
//        return cautareInLista(ht.tabela[pozitie], anCautat);
//    }
//    return c;
//}
//
//
//
//int main() {
//    HashTable ht = citireCladiriDinFisier("cladiri.txt", 7);
//    afisareTabela(ht);
//    int nrClustere = 0;
//    float* ani = anMediuConstructieCluster(ht, &nrClustere);
//    printf("\nPreturile medii:");
//    for (int i = 0; i < nrClustere; i++) {
//        printf("%.2f ", ani[i]);
//    }
//    printf("Cladirea Cautata: ");
//    Cladire c = getCladireDupaAnConstructie(ht, 1997);
//    afisareCladire(c);
//    
//    dezalocareTabela(&ht);
//    
//	return 0;
//}