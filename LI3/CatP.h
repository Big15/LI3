#ifndef CATP_H
#define CATP_H
#include "avl.h"
#include "List.h"

typedef struct CProdutos* Produtos;

Produtos criar_produtos();

Produtos insert_produtos(Produtos produtos, char* st);

List q2(Produtos produtos, List list, char c);

int check_produto(Produtos prod, char* cod);

#endif