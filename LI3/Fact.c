#include "Fact.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct avl_table TFact;

typedef struct InfFact {
    float total;
    float fN;
    float fP;
    int uni;
    int N;
    int P;    
} InfFact;

typedef struct LFact{
    char* cod;
    InfFact filial1;
    InfFact filial2;
    InfFact filial3;
    struct LFact *next;
} LFact;

typedef struct EFact {
    TFact *tree;
    LFact *lista;
} EFact;

int compare_strings3(const void *pa, const void *pb) {
    const LFact *a = pa;

    const LFact *b = pb;

    return strcmp(a->cod, b->cod);
}

InfFact novo_filial(){
    InfFact novo;
    novo.N = 0;
    novo.P = 0;
    novo.fN = 0;
    novo.fP = 0;
    novo.total = 0;
    novo.uni = 0;
    
    return novo;
}

Fact insert_produtosF(Fact fact,char* prod){
    LFact *novo = (LFact*) malloc(sizeof(LFact));
    novo->cod = (char*) malloc(sizeof (prod));

    strcpy(novo->cod, prod);
    novo->filial1 = novo_filial();
    novo->filial2 = novo_filial();
    novo->filial3 = novo_filial();
    novo->next = fact->lista;
    fact->lista = novo;
    
    avl_insert(fact->tree, novo);
    
    return fact;    
}

Fact criar_fact() {
    TFact *tree;
    LFact *list;
    Fact fact;

    tree = avl_create(compare_strings3, NULL, NULL);
    list = (LFact*) malloc(sizeof (LFact));
    
    
    fact = (Fact*) malloc(sizeof (Fact));
    
    fact->lista = list;
    fact->tree = tree;
    

    return fact;
}
/*
print_tree_structure(const struct avl_node *node, int level) {
    /* You can set the maximum level as high as you like.
       Most of the time, you'll want to debug code using small trees,
       so that a large |level| indicates a ``loop'', which is a bug. 
    if (level > 100) {
        printf("[...]");
        return;
    }

    if (node == NULL)
        return;

    printf("%s", *(int *) node->avl_data);
    if (node->avl_link[0] != NULL || node->avl_link[1] != NULL) {
        putchar('(');

        print_tree_structure(node->avl_link[0], level + 1);
        if (node->avl_link[1] != NULL) {
            putchar(',');
            print_tree_structure(node->avl_link[1], level + 1);
        }

        putchar(')');
    }
}

void print_whole_tree(const struct avl_table *tree, const char *title) {
    printf("%s: ", title);
    print_tree_structure(tree->avl_root, 0);
    putchar('\n');
}

void *print(Fact clientes){
    print_whole_tree(clientes->tree, "Cenas");
    printf("Count: %d", clientes->tree->avl_count);
}*/