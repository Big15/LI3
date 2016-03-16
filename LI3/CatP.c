#include "avl.h"
#include "CatP.h"
#include "CatC.h"
#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 8192

int compare_strings2(const void *pa, const void *pb) {
    const char **a = pa;

    const char **b = pb;


    return strcmp(*a, *b);
}

Produtos *criar_produtos() {
    TProdutos *tree;
    LProdutos *list;
    Produtos *produtos;

    tree = avl_create(compare_strings2, NULL, NULL);
    list = (LProdutos*) malloc(sizeof (LProdutos));
    produtos = (Produtos*) malloc(sizeof (Produtos));

    produtos->lista = list;
    produtos->tree = tree;

    return produtos;
}

void *insert_produtos(Produtos *produtos, char* st) {

    LProdutos *produto = (LProdutos*) malloc(sizeof (produtos->lista));
    produto->cod = (char*) malloc(sizeof (st));

    strcpy(produto->cod, st);
    produto->next = produtos->lista;
    produtos->lista = produto;
    printf("%s\n", produto->cod);



    avl_insert(produtos->tree, &produto->cod);



    return NULL;
}
