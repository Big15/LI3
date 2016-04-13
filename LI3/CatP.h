#ifndef CATP_H
#define CATP_H
#include "avl.h"

typedef struct CProdutos* Produtos;

Produtos criar_produtos();

Produtos insert_produtos(Produtos produtos, char* st);

#endif