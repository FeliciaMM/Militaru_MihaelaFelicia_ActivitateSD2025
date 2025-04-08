//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct Tablou {
//	int id;
//	char* pictor;
//	int nrReabilitari;
//	int* ani;
//};
//
//typedef struct Tablou Tablou;
//typedef struct Node Node;
//
//struct Node {
//	Tablou info;
//	Node* next;
//};
//
//Tablou citireTablouDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	Tablou t;
//
//	// Initialize everything to NULL or zero to avoid problems
//	t.pictor = NULL;
//	t.ani = NULL;
//	t.nrReabilitari = 0;
//	t.id = 0;
//
//	if (fgets(buffer, 100, file)) {
//		char* aux = strtok(buffer, sep);
//		if (!aux) return t;
//		t.id = atoi(aux);
//
//		aux = strtok(NULL, sep);
//		if (aux) {
//			t.pictor = (char*)malloc(strlen(aux) + 1);
//			strcpy(t.pictor, aux);
//		}
//		else {
//			t.pictor = NULL;
//		}
//
//		aux = strtok(NULL, sep);
//		if (aux) {
//			t.nrReabilitari = atoi(aux);
//		}
//
//		if (t.nrReabilitari > 0) {
//			t.ani = (int*)malloc(t.nrReabilitari * sizeof(int));
//			for (int i = 0; i < t.nrReabilitari; i++) {
//				aux = strtok(NULL, sep);
//				if (aux)
//					t.ani[i] = atoi(aux);
//				else
//					t.ani[i] = 0;
//			}
//		}
//	}
//
//	return t;
//}
//
//
//void afisareTablou(Tablou t){
//	printf("\nId: %d\n", t.id);
//	printf("Numele pictorului: %s\n", t.pictor);
//	printf("Nr reabilitari: %d\n", t.nrReabilitari);
//	printf("Reabilitarile au avut loc in anii:\n ");
//	for (int i = 0; i < t.nrReabilitari; i++) {
//	    printf("%d\n", t.ani[i]);
//	}
//}
//
//void afisareListaTablouri(Node *cap) {
//	while (cap!=NULL) {
//		afisareTablou(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugareLaInceput(Node** cap, Tablou tablouNou) {
//	Node* nou = (Node*)malloc(sizeof(Node));
//	nou->info = tablouNou;
//	nou->next = *cap;
//	*cap = nou;
//}
//
//void adaugareLaFinal(Node** cap, Tablou tablouNou) {
//	Node* nou = (Node*)malloc(sizeof(Node));
//	nou->info = tablouNou;
//	nou->next = NULL;
//	if (*cap) {
//		Node* p = *cap;
//		while (p->next) {
//			p = p->next;
//		}
//		p->next = nou;
//	}
//	else {
//		*cap = nou;
//	}
//}
//
//Node* citireListaDinFisier(const char* numeFisier) {
//	Node* cap = NULL;
//	FILE* file = fopen(numeFisier, "r");
//	if (file) {
//		while (!feof(file)) {
//			adaugareLaInceput(&cap, citireTablouDinFisier(file));
//		}
//	}
//	fclose(file);
//	return cap;
//}
//
//void dezalocare(Node** cap) {
//    while (*cap) {
//        Node* p = *cap;
//        *cap = p->next;
//
//        if (p->info.pictor != NULL) {
//            free(p->info.pictor);
//        }
//
//        if (p->info.ani != NULL) {
//            free(p->info.ani); 
//        }
//
//        free(p);  
//    }
//}
//
//int main() {
//	Node* cap = citireListaDinFisier("tablouri.txt");
//	afisareListaTablouri(cap);
//	dezalocare(&cap);
//	return 0;
//}