#include "CatP.h"
#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 8192
#define MAX_PRODUTOS 200000

typedef struct avl_table TProdutos;

typedef struct LProdutos {
    char* cod;
    struct LProdutos *next;
} LProdutos;

typedef struct CProdutos {
    TProdutos *tree;
    LProdutos *lista;
} CProdutos;

int compare_strings2(const void *pa, const void *pb) {
    const char **a = pa;

    const char **b = pb;


    return strcmp(*a, *b);
}

int travessia_treep_structure(const struct avl_node *node, int n, List* produtos) {    
    
    if (node->avl_link[0] != NULL){
        n = travessia_treep_structure(node->avl_link[0], n, produtos);
    }    
        produtos = add_string_l(produtos, *(int*) node->avl_data);
        //if(n < 20)  printf("%s - %d\n", (*clientes)->cliente[n], n);
        n++;
    if(node->avl_link[1] != NULL){
        n = travessia_treep_structure(node->avl_link[1], n, produtos);
    }    
    
    return n;
}

int travessia_tree_q2(const struct avl_node *node, int n, List produtos, char c) {    
    char* ch = strdup( *(int*) node->avl_data);
    if (node->avl_link[0] != NULL){
        n = travessia_tree_q2(node->avl_link[0], n, produtos, c);
    }
    if(ch[0] == c){
        produtos = add_string_l(produtos, *(int*) node->avl_data);
        n++;
    }
    if(node->avl_link[1] != NULL){
        n = travessia_tree_q2(node->avl_link[1], n, produtos, c);
    }    
    
    return n;
}

List q2(Produtos produtos, List list, char c){
    int n;
    n = travessia_tree_q2(produtos->tree->avl_root, 0, list, c);
    
    return list;
}

List cria_lprodutos(Produtos produtos){
    List novo = (List*) malloc(sizeof(List) * MAX_PRODUTOS);
    int n;
    n = travessia_treep_structure(produtos->tree->avl_root, 0, &novo);
    
    return novo;
}

int check_produto(Produtos prod, char* cod){
    int n;
    LProdutos *novo = (LProdutos*) malloc(sizeof (LProdutos));
    novo->cod = strdup(cod);
    novo = avl_find(prod->tree, novo);
    
    if(novo == NULL)
        n = 1;
    else
        n = 0;
    return n;
}


Produtos criar_produtos() {
    TProdutos *tree;
    LProdutos *list;
    Produtos produtos;

    tree = avl_create(compare_strings2, NULL, NULL);
    list = (LProdutos*) malloc(sizeof (LProdutos));
    produtos = (Produtos*) malloc(sizeof (Produtos));

    produtos->lista = list;
    produtos->tree = tree;

    return produtos;
}

Produtos insert_produtos(Produtos produtos, char* st) {

    LProdutos *produto = (LProdutos*) malloc(sizeof (produtos->lista));
    produto->cod = (char*) malloc(sizeof (st));

    strcpy(produto->cod, st);
    produto->next = produtos->lista;
    produtos->lista = produto;



    avl_insert(produtos->tree, &produto->cod);



    return produtos;
}