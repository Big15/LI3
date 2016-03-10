#include "avl.h"

typedef struct avl_table TClientes;

typedef struct LClientes{
    char* cod;
    struct LClientes *next;    
}LClientes;

typedef struct Clientes{
    TClientes *tree;
    LClientes *lista;
}Clientes;
