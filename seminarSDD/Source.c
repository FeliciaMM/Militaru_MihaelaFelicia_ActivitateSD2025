#define CRT_SECURE_NO_WARNINGS_

#include<stdio.h>
#include<malloc.h>

struct Masina {
	int id;
	//int ;
	//char* ;
	//float ;
	//char ;
};
struct Masina initializare(/*parametri necesari*/) {
	struct Masina s;
	s.id = 1;
	return s;
}

void afisare(struct Masina s) {
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
	}
}

void afisareVector(struct Masina* vector, int nrElemente) {
	//afisarea elementelor din vector apeland functia afisare
}

struct Masina* copiazaPrimeleNElemente(struct Masina* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Masina* vectorNou = NULL;

	return vectorNou;
}

void dezalocare(struct Masina** vector, int* nrElemente) {
	//dezalocam elementele din vector si vectorul
}

void copiazaAnumiteElemente(struct Masina* vector, char nrElemente, float prag, struct Masina** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
}

struct Masina getPrimulElementConditionat(struct Masina* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Masina s;
	s.id = 1;

	return s;
}



int main() {
	struct Masina* vector;
	int nrElem = 3;
	vector = (struct Masina)malloc(nrElem * sizeof(struct Masina));

	vector[0] = initializare(1, 3, 'Dacia', 40, '5');
	vector[1] = initializare(2, 5, 'Honda', 30, '6');
	vector[2] = initializare(3, 4, 'Dacia', 50, '3');
	afisare(vector, nrElem);



	return 0;
}