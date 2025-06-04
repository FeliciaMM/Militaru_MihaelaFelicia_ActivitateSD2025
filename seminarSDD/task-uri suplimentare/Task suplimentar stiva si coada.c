#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}


//STIVA


typedef struct Nod Nod;
struct Nod {
	Masina info;
	Nod* next;
};

void pushStack(Nod** stiva, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masina;
	nou->next = (*stiva);
	(*stiva) = nou;
}

Masina popStack(Nod** stiva) {
	Masina m;
	if ((*stiva) != NULL) {
		Nod* temp = *stiva;
		m = temp->info;
		*stiva = temp->next;
		free(temp);
	}
	else {
		m.id = -1;
		m.nrUsi = 0;
		m.pret = 0.0f;
		m.model = NULL;
		m.numeSofer = NULL;
		m.serie = 0;
	}
	return m;
}

Nod * citireStackMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* stiva = NULL;
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		pushStack(&stiva, m);
	}
	fclose(f);
	return stiva;
}
	
void dezalocareStivaDeMasini(Nod** stiva) {
	while ((*stiva) != NULL) {
		Masina m = popStack(stiva);
		free(m.numeSofer);
		free(m.model);
	
	}
}

struct StackVector {
	Masina* masini;
	int top;
	int capacitate;
};
typedef struct StackVector StackVector;

StackVector creareStackVector(int capacitate) {
	StackVector sv;
	sv.masini = (Masina*)malloc(sizeof(Masina) * capacitate);
	sv.top = -1;
	sv.capacitate = capacitate;
	return sv;
}

void pushStackVector(StackVector* sv, Masina m) {
	if (sv->top < sv->capacitate - 1) {
		sv->masini[++(sv->top)] = m;
	}
}

Masina popStackVector(StackVector* sv) {
	if (sv->top >= 0)
		return sv->masini[(sv->top)--];
	Masina m = { -1, 0, 0.0f, NULL, NULL, 0 };
	return m;
}

void dezalocareStackVector(StackVector* sv) {
	for (int i = 0; i <= sv->top; i++) {
		free(sv->masini[i].model);
		free(sv->masini[i].numeSofer);
	}
	free(sv->masini);
}

typedef struct NodeLDS NodeLDS;

struct NodeLDS {
	Masina info;
	NodeLDS* next;
	NodeLDS* prev;
};

struct ListaDublaS {
	NodeLDS* first;
	NodeLDS* last;
};

typedef struct ListaDublaS ListaDublaS;

void pushStackLD(ListaDublaS* stiva, Masina m) {
	NodeLDS* nou = (NodeLDS*)malloc(sizeof(NodeLDS));
	nou->info = m;
	nou->prev = NULL;
	nou->next = stiva->first;
	if (stiva->first != NULL) {
		stiva->first->prev = nou;
	}
	else {
		stiva->last = nou;
	}
	stiva->first = nou;
}

Masina popStackLD(ListaDublaS* stiva) {
	Masina m = { -1, 0, 0.0f, NULL, NULL, 0 };
	if (stiva->first != NULL) {
		NodeLDS* temp = stiva->first;
		m = temp->info;
		stiva->first = temp->next;
		if (stiva->first != NULL)
			stiva->first->prev = NULL;
		else
			stiva->last = NULL;
		free(temp);
	}
	return m;
}



//COADA 

typedef struct NodDublu NodDublu;
typedef struct ListaDubla ListaDubla;
struct NodDublu {
	Masina info;
	NodDublu* next;
	NodDublu* prev;
};

struct ListaDubla {
	NodDublu* first;
	NodDublu* last;
};

typedef struct QueueVector QueueVector;

struct QueueVector {
	Masina* masini;
	int capacitate;
	int start;
	int end;
	int nrElemente;
};

QueueVector creareQueueVector(int capacitate) {
	QueueVector qv;
	qv.masini = (Masina*)malloc(sizeof(Masina) * capacitate);
	qv.capacitate = capacitate;
	qv.start = 0;
	qv.end = 0;
	qv.nrElemente = 0;
	return qv;
}

void enqueueVector(QueueVector* qv, Masina m) {
	if (qv->nrElemente < qv->capacitate) {
		qv->masini[qv->end] = m;
		qv->end = (qv->end + 1) % qv->capacitate;
		qv->nrElemente++;
	}
}

Masina dequeueVector(QueueVector* qv) {
	if (qv->nrElemente > 0) {
		Masina m = qv->masini[qv->start];
		qv->start = (qv->start + 1) % qv->capacitate;
		qv->nrElemente--;
		return m;
	}
	Masina m = { -1, 0, 0.0f, NULL, NULL, 0 };
	return m;
}

void dezalocareQueueVector(QueueVector* qv) {
	for (int i = 0; i < qv->nrElemente; i++) {
		int idx = (qv->start + i) % qv->capacitate;
		free(qv->masini[idx].model);
		free(qv->masini[idx].numeSofer);
	}
	free(qv->masini);
}

typedef struct NodSimplu NodSimplu;

struct NodSimplu {
	Masina info;
	NodSimplu* next;
};

void enqueueLSI(NodSimplu** front, NodSimplu** rear, Masina m) {
	NodSimplu* nou = (NodSimplu*)malloc(sizeof(NodSimplu));
	nou->info = m;
	nou->next = NULL;

	if (*rear != NULL) {
		(*rear)->next = nou;
	}
	else {
		*front = nou; 
	}

	*rear = nou;
}


Masina dequeueLSI(NodSimplu** front, NodSimplu** rear) {
	Masina m = { -1, 0, 0.0f, NULL, NULL, 0 };
	if (*front != NULL) {
		NodSimplu* temp = *front;
		m = temp->info;
		*front = (*front)->next;

		if (*front == NULL) {
			*rear = NULL; // Coada a devenit goală
		}

		free(temp);
	}
	return m;
}

void dezalocareQueueLSI(NodSimplu** front, NodSimplu** rear) {
	while (*front != NULL) {
		Masina m = dequeueLSI(front, rear);
		free(m.model);
		free(m.numeSofer);
	}
}

int main() {
	/*Nod* stiva = citireStackMasiniDinFisier("masini.txt");
//	Masina m = popStack(&stiva);
//	afisareMasina(m);
//	printf("Nr noduri: %d", size(stiva));*/

	return 0;
}