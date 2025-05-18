//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
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
//
////creare structura pentru un nod dintr-un arbore binar de cautare
//
////SA IMPLEMENTEZE FELICIA CITIREA SA NU MAI FIE TUTA
//
////int calculeazaInaltimeArbore(/*arbore de masini*/) {
////	//calculeaza inaltimea arborelui care este data de 
////	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
////	return 0;
////}
//
////ALTE FUNCTII NECESARE:
//// - aici veti adauga noile functii de care aveti nevoie.
//
//void adaugaMasinaInArboreEchilibrat(/*arborele de masini*/ Masina masinaNoua) {
//	//adauga o noua masina pe care o primim ca parametru in arbore,
//	//astfel incat sa respecte principiile de arbore binar de cautare ECHILIBRAT
//	//dupa o anumita cheie pe care o decideti - poate fi ID
//}
//
//void* citireArboreDeMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//}
//
//void afisareMasiniDinArbore(/*arbore de masini*/) {
//	//afiseaza toate elemente de tip masina din arborele creat
//	//prin apelarea functiei afisareMasina()
//	//parcurgerea arborelui poate fi realizata in TREI moduri
//	//folositi toate cele TREI moduri de parcurgere
//}
//
//void dezalocareArboreDeMasini(/*arbore de masini*/) {
//	//sunt dezalocate toate masinile si arborele de elemente
//}
//
////Preluati urmatoarele functii din laboratorul precedent.
////Acestea ar trebuie sa functioneze pe noul arbore echilibrat.
//
//Masina getMasinaByID(/*arborele de masini*/int id);
//
//int determinaNumarNoduri(/*arborele de masini*/);
//
//float calculeazaPretTotal(/*arbore de masini*/);
//
//float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer);
//
//int main() {
//
//
//	return 0;
//}