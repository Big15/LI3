#ifndef CATC_H
#define CATC_H
#include "avl.h"

typedef struct CClientes* Clientes;

typedef struct ListClientes* LstClientes;

Clientes criar_clientes();

Clientes insert_clientes (Clientes clientes, char* st);

LstClientes cria_lclientes(Clientes clientes);

int check_cliente(Clientes cli, char* cod);


#endif