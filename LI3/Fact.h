#ifndef FACT_H
#define FACT_H
#include "avl.h"
#include "List.h"

typedef struct EFact* Fact;

Fact criar_fact();

Fact insert_produtosF(Fact fact,char* prod);

Fact insert_vendasF(Fact fact, char* prod, float valor, int uni, char* promo, int mes, int filial);

void teste(Fact fact, char* prod);

List q3(Fact fact, List list, int mes, char* cod, int tipo);

List q4(Fact fact, List list, int tipo);

List q6(Fact fact, List list, int mes1, int mes2);

List q10_fact(Fact fact, List list, int n);

List q12_fact(Fact fact, List list);

#endif /* FACT_H */