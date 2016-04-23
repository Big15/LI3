#include "CatC.h"
#include "Codigo.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct avl_table TClientes;

typedef struct LClientes{
    Codigo cod;
    struct LClientes *next;    
}LClientes;

typedef struct CClientes{
    TClientes *tree;
    LClientes *lista;
}CClientes;

int compare_strings (const void *pa, const void *pb){
    const LClientes *a = pa;
    const LClientes *b = pb;
    
    return strcmp(get_codigo(a->cod), get_codigo(b->cod));
}


int check_cliente(Clientes cli, char* cod){
    int n;
    LClientes *novo = (LClientes*) malloc(sizeof (LClientes));
    novo->cod = (Codigo*) malloc(sizeof (Codigo));
    novo->cod = set_codigo(novo->cod, cod);
    novo = avl_find(cli->tree, novo);
    
    if(novo == NULL)
        n = 1;
    else
        n = 0;
    return n;
}

Clientes criar_clientes(){
    TClientes *tree;   
    LClientes *list;    
    Clientes clientes;
    
    tree = avl_create (compare_strings, NULL, NULL);
    list = (LClientes*) malloc(sizeof(LClientes));
    list = NULL;
    clientes = (Clientes*) malloc(sizeof(Clientes));
    
    clientes->lista = list;
    clientes->tree = tree;
    
    return clientes;
}

Clientes insert_clientes (Clientes clientes, char* st){
    
    LClientes *cliente = (LClientes*) malloc(sizeof(LClientes));
    cliente->cod = (Codigo*) malloc(sizeof (Codigo));

    cliente->cod = set_codigo(cliente->cod, st);
    
    cliente->next = clientes->lista;
    clientes->lista = cliente;
    
    avl_insert(clientes->tree, cliente); 
            
    
    return clientes;
}


