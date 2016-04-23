#ifndef FILIAL_H
#define FILIAL_H

#include "avl.h"
#include "List.h"

typedef struct EFilial* Filial;

Filial instert_clientesFil(Filial fil, char* cod);

Filial insert_vendas_Filial(Filial fil, char* prod, float valor, int uni, char* promo, char* cli, int mes, int filial);

Filial criar_filial();

#endif /* FILIAL_H */

