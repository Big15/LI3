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
    InfFact info;
    struct LFact *next;
} LFact;

typedef struct EFact {
    TFact *tree;
    LFact *lista;
} EFact;

typedef struct AFact{
    EFact afact[3];
} AFact;

int compare_strings3(const void *pa, const void *pb) {
    const char **a = pa;

    const char **b = pb;


    return strcmp(*a, *b);
}

Fact criar_fact() {
    TFact *tree1;
    TFact *tree2;
    TFact *tree3;
    LFact *list1;
    LFact *list2;
    LFact *list3;
    Fact fact;

    tree1 = avl_create(compare_strings3, NULL, NULL);
    list1 = (LFact*) malloc(sizeof (LFact));
    tree2 = avl_create(compare_strings3, NULL, NULL);
    list2 = (LFact*) malloc(sizeof (LFact));
    tree3 = avl_create(compare_strings3, NULL, NULL);
    list3 = (LFact*) malloc(sizeof (LFact));
    
    fact = (Fact*) malloc(sizeof (Fact));

    fact->afact[0].lista = list1;
    fact->afact[0].tree = tree1;
    
    fact->afact[1].lista = list2;
    fact->afact[1].tree = tree2;
    
    fact->afact[2].lista = list3;
    fact->afact[2].tree = tree3;

    return fact;
}