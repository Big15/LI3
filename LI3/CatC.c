#include "CatC.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct avl_table TClientes;

typedef struct LClientes{
    char* cod;
    struct LClientes *next;    
}LClientes;

typedef struct CClientes{
    TClientes *tree;
    LClientes *lista;
}CClientes;

int compare_strings (const void *pa, const void *pb){
    const char **a = pa;
    const char **b = pb;
    
    return strcmp(*a, *b);
}


int check_cliente(Clientes cli, char* cod){
    int n;
    LClientes *novo = (LClientes*) malloc(sizeof (LClientes));
    novo->cod = strdup(cod);
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
    LClientes *cliente = (LClientes*) malloc(sizeof(clientes->lista));
    cliente->cod =(char*) malloc(sizeof(st));    
    
    strcpy(cliente->cod, st);
    cliente->next = clientes->lista;
    clientes->lista = cliente;
    
    avl_insert(clientes->tree, &cliente->cod); 
            
    
    return clientes;
}


