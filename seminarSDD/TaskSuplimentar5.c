//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//typedef struct Nod Nod;
//
//struct Nod {
//	Masina info;
//	struct Nod* next;
//};
//
//
//
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	Masina m1;
//	fgets(buffer, 100, file);
//	char* aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	m1.nrUsi = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	m1.pret = atof(aux);
//
//	aux = strtok(NULL, sep);
//	m1.model = (char*)malloc(strlen(aux) + 1);
//	strcpy(m1.model, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = (char*)malloc(strlen(aux) + 1);
//	strcpy(m1.numeSofer, aux);
//
//	m1.serie = *strtok(NULL, sep);
//
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareListaMasini(Nod* cap) {
//	while (cap != NULL) {
//		afisareMasina(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
//	//creem un nod nou
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	//punem informatia noua in el
//	nodNou->info = masinaNoua;
//	nodNou->next = NULL;
//	//atata timp cat avem cap
//	if (*cap) {
//		//creem un nod temporar cu care sa mergem inainte
//		Nod* temp = *cap;
//		//cat temporarul are next inaintam
//		while (temp->next) {
//			temp = temp->next;
//		}
//		//cand nu mai exista next ne oprim si punem nodul cel nou la finalul liste
//		temp->next = nodNou;
//	}
//	else {
//		//daca nu avem cap deloc, nodul nou devin cap
//		*cap = nodNou;
//	}
//}
//
//void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
//	//nod nou
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	//punem info noua in nod
//	nodNou->info = masinaNoua;
//	//adaugam nodul inaintea nodului care este cap (poate fi si null)
//	nodNou->next = *cap;
//	//noul nod devine cap
//	*cap = nodNou;
//
//}
//
//void adaugaInListaCrescatorPret(Nod** cap, Masina masinaNoua) {
//	Nod* nod = (Nod*)malloc(sizeof(Nod));
//	nod->info = masinaNoua;
//	nod->next = NULL;
//	if (*cap == NULL || (*cap)->info.pret > masinaNoua.pret) {
//		nod->next = *cap;
//		*cap = nod;
//		return;
//	}
//	Nod* temp = *cap;
//	while (temp->next != NULL && temp->next->info.pret < masinaNoua.pret) {
//		temp = temp->next;
//	}
//
//	nod->next = temp->next;
//	temp->next = nod;
//}
//
//
//void* citireListaMasiniDinFisier(const char* numeFisier) {
//	//incepem cu o lista goala
//	Nod* cap = NULL;
//	//deschidem fisierul
//	FILE* file = fopen(numeFisier, "r");
//	//daca avem fisier
//	if (file) {
//		//cat nu suntem la sfarsitul dilei
//		while (!feof(file)) {
//			//adauga la inceput masina citita din fisier
//			adaugaInListaCrescatorPret(&cap, citireMasinaDinFisier(file));
//		}
//	}
//	//IMPORTANT : inchidem fisierul
//	fclose(file);
//	//returnam lista
//	return cap;
//}
//
//
//void dezalocareListaMasini(Nod** cap) {
//	while (*cap) {
//		Nod* temp = *cap;
//		(*cap) = temp->next;
//		if (temp->info.model) {
//			free(temp->info.model);
//		}
//		if (temp->info.numeSofer) {
//			free(temp->info.numeSofer);
//		}
//		free(temp);
//	}
//}
//
//float calculeazaPretMediu(Nod* lista) {
//	if (!lista) {
//		return 0;
//	}
//
//	float suma = 0;
//	int lungime = 0;
//	Nod* temp = lista;
//	while (temp) {
//		suma += temp->info.pret;
//		lungime++;
//		temp = temp->next;
//
//	}
//	float medie = suma / lungime;
//	return medie;
//}
//
//void stergeMasiniDinSeria(Nod** cap, char serieCautata) {
//	while ((*cap) && (*cap)->info.serie == serieCautata) {
//		Nod* aux = *cap;
//		(*cap) = aux->next;
//		if (aux->info.numeSofer) {
//			free(aux->info.numeSofer);
//		}
//		if (aux->info.model) {
//			free(aux->info.model);
//		}
//		free(aux);
//	}
//	if ((*cap)) {
//		Nod* p = *cap;
//		while (p) {
//			while (p->next && p->next->info.serie != serieCautata) {
//				p = p->next;
//			}
//			if (p->next) {
//				Nod* aux = p->next;
//				p->next = aux->next;
//				if (aux->info.numeSofer) {
//					free(aux->info.numeSofer);
//				}
//				if (aux->info.model) {
//					free(aux->info.model);
//				}
//				free(aux);
//			}
//			else {
//				p = NULL;
//			}
//		}
//	}
//
//}
//
//float calculeazaPretulMasinilorUnuiSofer(Nod* cap, const char* numeSofer) {
//	float suma = 0;
//	while (cap) {
//		if (strcmp(cap->info.numeSofer, numeSofer) == 0) {
//			suma += cap->info.pret;
//		}
//		cap = cap->next;
//	}
//	return suma;
//}
//
//void stergeNodLaPozitiaData(Nod** cap, const pozitie) {
//	int index = 0;
//	Nod* temp = *cap;
//
//	if (temp == NULL) {
//	printf("Lista este goala\n");
//	return 0;
//	}
//
//	if (pozitie == 0) {
//		*cap = temp->next;
//		free(temp->info.model);
//		free(temp->info.numeSofer);
//		free(temp);
//		return;
//	}
//	while (temp!=NULL && index<pozitie) {
//		if (index == pozitie - 1) {
//			Nod* aux = temp->next;
//			temp->next = aux->next;
//			free(aux->info.model);
//			free(aux->info.numeSofer);
//			free(aux);
//			return 0;
//		}
//		temp = temp->next;
//		index++;
//		
//	}
//	return 0;
//}
//
//
//int main() {
//	Nod* cap = citireListaMasiniDinFisier("masini.txt");
//	afisareListaMasini(cap);
//
//
//	float mediePret = calculeazaPretMediu(cap);
//	printf("Media preturilor este: %.2f\n", mediePret);
//
//	float mediePretSofer = calculeazaPretulMasinilorUnuiSofer(cap, "Ionescu");
//	printf("Media preturilor masinilor lui Ionescu este: %.2f\n", mediePretSofer);
//	
//	int pozitieDeSters = 3;
//	printf("Stergem nodul de la pozitia %d\n", pozitieDeSters);
//	stergeNodLaPozitiaData(&cap, pozitieDeSters);
//
//	printf("Lista dupa stergere:\n");
//	afisareListaMasini(cap);
//	
//	dezalocareListaMasini(&cap);
//
//	
//
//	return 0;
//}