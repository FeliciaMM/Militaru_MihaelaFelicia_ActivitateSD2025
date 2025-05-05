//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct Suc {
//	int id;
//	char* nume;
//};
//typedef struct Suc Suc;
//typedef struct Node Node;
//typedef struct HashTable HashTable;
//
//struct Node {
//	Suc info;
//	Node* next;
//};
//
//struct HashTable {
//	int dim;
//	Node** tabela;
//};
//
//Suc citireDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	char* aux;
//	Suc s;
//	s.id = -1;
//	s.nume = NULL;
//	if (fgets(buffer, 100, file)) {
//		aux = strtok(buffer, sep);
//		if (!aux)return s;
//		s.id = atoi(aux);
//		aux = strtok(NULL, sep);
//		s.nume = (char*)malloc(strlen(aux) + 1);
//		strcpy(s.nume, aux);
//	}
//	return s;
//}
//
//void afisareSuc(Suc s) {
//	printf("\nId: %d", s.id);
//	printf("\nNume: %s\n", s.nume);
//}
//
//void afisareListSucuri(Node* cap) {
//	while (cap) {
//		afisareSuc(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugareSucInLista(Node** cap, Suc sucNou) {
//	Node* nou = (Node*)malloc(sizeof(Node));
//	nou->info = sucNou;
//	nou->next = *cap;
//	*cap = nou;
//}
//
//HashTable initializareTabela(int dim) {
//	HashTable ht;
//	ht.dim = dim;
//	ht.tabela = (Node*)malloc(sizeof(Node*) * dim);
//	for (int i = 0; i < dim; i++) {
//		ht.tabela[i] = NULL;
//	}
//	return ht;
//}
//
//int calculeazaHash(int id, int dim) {
//	return id % dim;
//}
//
//void inserareSucuriInTabela(HashTable ht,Suc suc) {
//	int pozitie = calculeazaHash(suc.id, ht.dim);
//	if (ht.tabela[pozitie] == NULL) {
//		ht.tabela[pozitie] = (Node*)malloc(sizeof(Node));
//		ht.tabela[pozitie]->info = suc;
//		ht.tabela[pozitie]->next = NULL;
//	}
//	else {
//		adaugareSucInLista(ht.tabela[pozitie], suc);
//	}
//}
//
//
//HashTable citireSucuriDinFisier(const char* numeFisier, int dimensiune) {
//	HashTable hash = initializareTabela(dimensiune);
//	FILE* file = fopen(numeFisier, "r");
//	if (file) {
//		while (!feof(file)) {
//			Suc suc = citireDinFisier(file);
//			inserareSucuriInTabela(hash, suc);
//		}
//	}
//	fclose(file);
//	return hash;
//}
//
//void afisareTabelaClusters(HashTable ht) {
//	for (int i = 0; i < ht.dim; i++) {
//		if (ht.tabela[i] != NULL) {
//			printf("\nClusterul %d: \n", i);
//			afisareListSucuri(ht.tabela[i]);
//		}
//		else {
//			printf("\nCluserul %d este gol\n", i);
//		}
//	}
//}
//
//void dezalocareLista(Node** cap) {
//	Node* p = *cap;
//	while (p) {
//		Node* temp = p;
//		p = p->next;
//		if (temp->info.nume ) {
//			free(temp->info.nume);
//		}
//		free(temp);
//	}
//	*cap = NULL;
//	
//}
//
//void dezalocareTabela(HashTable* ht) {
//	for (int i = 0; i < ht->dim; i++) {
//		dezalocareLista(&(ht->tabela[i]));
//	}
//	free(ht->tabela);
//	ht->tabela = NULL;
//	ht->dim = 0;
//}
//
//int main() {
//	HashTable ht = citireSucuriDinFisier("sucuri.txt", 5);
//	afisareTabelaClusters(ht);
//	dezalocareTabela(&ht);
//	return 0;
//}