#ifndef FILIAL_H
#define FILIAL_H

#include "avl.h"
#include "List.h"

typedef struct EFilial* Filial;

Filial instert_clientesFil(Filial fil, char* cod);

Filial insert_vendas_Filial(Filial fil, char* prod, float valor, int uni, char* promo, char* cli, int mes, int filial);

Filial criar_filial();

List q5(Filial fil, List list, char* cod);

List q7(Filial fil, List list);

List q8(Filial fil, List list, char* prod, int filial);

List q9(Filial fil, List list, char* cli, int mes);

List q10_fili(Filial fil, List l, int t);

List q11(Filial fil, List list, char* cli);

List q12_fili(Filial fil, List list, int t);

#endif /* FILIAL_H */

