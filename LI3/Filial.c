#include "Filial.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct avl_table TFilial;

typedef struct InfFil {
    int total;
    float facturado;
    int N;
    int P;
}InfFil;

typedef struct LProdF {
    char* cod;
    int total;
    InfFil filial1[13];
    InfFil filial2[13];
    InfFil filial3[13];
    struct LProdF *next;
}LProdF;

typedef struct avl_table TProdF;


typedef struct EProdF{
    TProdF *tree;
    LProdF *lista;
} EProdF;


typedef struct LFilial{
    char* cod;
    int total[13][4];
    EProdF lProdsFil;
    struct LFilial *next;
} LFilial;

typedef struct EFilial{
    TFilial *tree;
    LFilial *lista;
} EFilial;

int compare_strings4(const void *pa, const void *pb) {
    const LFilial *a = pa;

    const LFilial *b = pb;

    return strcmp(a->cod, b->cod);
}

int compare_unidades(const void *pa, const void *pb) {
    const LProdF *a = pa;

    const LProdF *b = pb;
    
    if(a->total == b->total)
        return 0;
    else if(a->total > b->total)
        return 1;
    else
        return -1;    
}

int travessia_tree_q7(const struct avl_node *node) {
    int i;
    int n = 0;
    int n1 = 0, n2 = 0, n3 = 0;
    LFilial *old = node->avl_data;
    if (node->avl_link[0] != NULL){
        n += travessia_tree_q7(node->avl_link[0]);
    }
    
    for(i = 1; i <= 12; i++){
        n1 += old->total[i][1];
        n2 += old->total[i][2];
        n3 += old->total[i][3];
    }
    if(n1 > 0 && n2 > 0 && n3 > 0)
        n++;    
    
    if(node->avl_link[1] != NULL){
        n += travessia_tree_q7(node->avl_link[1]);
    }    
    
    return n;
}

int travessia_tree_q8(const struct avl_node *node, char* prod, int filial, List list) {
    int i;
    int n = 0;
    int n1 = 0, p = 0;
    
    LProdF *newL = (LProdF*) malloc(sizeof (LProdF));    
    newL->cod = (char*) malloc(sizeof (prod));
    strcpy(newL->cod, prod);
    
    LProdF *oldL;    
    LFilial *old = node->avl_data;
    oldL = avl_find(old->lProdsFil.tree, newL);
    
    if (node->avl_link[0] != NULL){
        n += travessia_tree_q8(node->avl_link[0], prod, filial, list);
    }
    
    if(oldL != NULL){       
        for(i = 1; i <= 12; i++){
            switch(filial){
                case 1:
                    if(oldL->filial1[i].N > 0)
                        n1++;
                    if(oldL->filial1[i].P > 0)
                        p++;
                break;
                case 2:
                    if(oldL->filial2[i].N > 0)
                        n1++;
                    if(oldL->filial2[i].P > 0)
                        p++;
                break;
                case 3:
                    if(oldL->filial3[i].N > 0)
                        n1++;
                    if(oldL->filial3[i].P > 0)
                        p++;
                break;
            }
        }
        if(n1){
            concat_string_l(list, old->cod, 0);
            concat_string_l(list, " ", 0);
            //printf("%s ", old->cod);
        }
        if(p){
            concat_string_l(list, old->cod, 1);
            concat_string_l(list, " ", 1);
            //printf("%s ", old->cod);
        }
        
    }
    
    if(node->avl_link[1] != NULL){
        n += travessia_tree_q8(node->avl_link[1], prod, filial, list);
    }    
    return n;
}

List q8(Filial fil, List list, char* prod, int filial){
    
    add_string_l(list, "N: ");
    add_string_l(list, "P: ");
    travessia_tree_q8(fil->tree->avl_root, prod, filial, list);

    return list;
}

List q7(Filial fil, List list){
    int n = travessia_tree_q7(fil->tree->avl_root);
    printf("%d clientes que compraram em todas as filiais\n", n);
    
    return list;
}


List q5(Filial fil, List list, char* cod){
    LFilial *novo = (LFilial*) malloc(sizeof (LFilial)); 
    LFilial *old;
    int i;
    
    novo->cod = (char*) malloc(sizeof (cod));
    strcpy(novo->cod, cod); 
    
    old = avl_find(fil->tree, novo);
    
    if(old != NULL){
        printf("Mes   Filial1   Filial2     Filial3\n");
        for(i = 1; i <= 12; i++){
            printf("%d   %d   %d     %d\n", i, old->total[i][1], old->total[i][2], old->total[i][3]);
        }
    }
    return list;
}


int travessia_tree_q12_fili(const struct avl_node *node, int n) {    
    LFilial *old = node->avl_data;    
    int i, n1 = 0, n2 = 0, n3 = 0;
    if (node->avl_link[0] != NULL) {
        n = travessia_tree_q12_fili(node->avl_link[0], n);
    }
    for (i = 1; i <= 12; i++) {
        n1 += old->total[i][1];
        n1 += old->total[i][2];
        n1 += old->total[i][3];        
    }
    if (n1 == 0) {
            //printf("%s\n", old->cod);
            n++;
        }

    if (node->avl_link[1] != NULL){
        n = travessia_tree_q12_fili(node->avl_link[1], n);
    }    
    
    return n;
}

List q12_fili(Filial fil, List list){
    int n;
    char* res = (char*) malloc (sizeof(char*)*30);
    n = travessia_tree_q12_fili(fil->tree->avl_root, 0);
    sprintf(res, "Clientes que nunca compraram: %d", n);
    list = add_string_l(list, res);    
    
    return list;
}

InfFil novo_filial_filial(){
    InfFil novo;
    novo.N = 0;
    novo.P = 0;
    novo.facturado = 0;
    novo.total = 0;
    
    return novo;    
}

Filial insert_vendas_Filial(Filial fil, char* prod, float valor, int uni, char* promo, char* cli, int mes, int filial){
    LFilial *novo = (LFilial*) malloc(sizeof (LFilial));
    LFilial *old;
    LProdF *newL = (LProdF*) malloc(sizeof (LProdF));
    LProdF *oldL;    
        
    
    
    
    
    int i, flag = 1;
    novo->cod = (char*) malloc(sizeof (cli));
    strcpy(novo->cod, cli);  
    
    newL->cod = (char*) malloc(sizeof (prod));
    strcpy(newL->cod, prod);

    old = avl_find(fil->tree, novo);
    
    if(old != NULL){        
        oldL = avl_find(old->lProdsFil.tree, newL);
        if(oldL != NULL){
            //printf("FOUND1!");
            switch(filial){
                case 1:
                    if (!strcmp(promo, "N")) {
                    oldL->filial1[mes].N += uni;
                    oldL->filial1[mes].facturado += (valor*uni);
                    oldL->filial1[mes].total += uni;
                } else {
                    oldL->filial1[mes].P += uni;
                    oldL->filial1[mes].facturado += (valor*uni);
                    oldL->filial1[mes].total += uni;
                }
                    oldL->total += uni;
                    old->total[mes][1] += uni;
                break;
                case 2:
                    if (!strcmp(promo, "N")) {
                    oldL->filial2[mes].N += uni;
                    oldL->filial2[mes].facturado += (valor*uni);
                    oldL->filial2[mes].total += uni;
                } else {
                    oldL->filial2[mes].P += uni;
                    oldL->filial2[mes].facturado += (valor*uni);
                    oldL->filial2[mes].total += uni;
                }
                    oldL->total += uni;
                    old->total[mes][2] += uni;
                break;
                case 3:
                    if (!strcmp(promo, "N")) {
                    oldL->filial3[mes].N += uni;
                    oldL->filial3[mes].facturado += (valor*uni);
                    oldL->filial3[mes].total += uni;
                } else {
                    oldL->filial3[mes].P += uni;
                    oldL->filial3[mes].facturado += (valor*uni);
                    oldL->filial3[mes].total += uni;
                }
                    oldL->total += uni;
                    old->total[mes][3] += uni;
                break;
            }
        }
        else{
            for(i = 1; i <= 12; i++){
                newL->filial1[i] = novo_filial_filial();
                newL->filial2[i] = novo_filial_filial();
                newL->filial3[i] = novo_filial_filial();                
            }
            switch(filial){
                case 1:
                    if (!strcmp(promo, "N")) {
                    newL->filial1[mes].N += uni;
                    newL->filial1[mes].facturado += (valor*uni);
                    newL->filial1[mes].total += uni;
                } else {
                    newL->filial1[mes].P += uni;
                    newL->filial1[mes].facturado += (valor*uni);
                    newL->filial1[mes].total += uni;
                }
                    newL->total += uni;
                    old->total[mes][1] += uni;
                break;
                case 2:
                    if (!strcmp(promo, "N")) {
                    newL->filial2[mes].N += uni;
                    newL->filial2[mes].facturado += (valor*uni);
                    newL->filial2[mes].total += uni;
                } else {
                    newL->filial2[mes].P += uni;
                    newL->filial2[mes].facturado += (valor*uni);
                    newL->filial2[mes].total += uni;
                }
                    newL->total += uni;
                    old->total[mes][2] += uni;
                break;
                case 3:
                    if (!strcmp(promo, "N")) {
                    newL->filial3[mes].N += uni;
                    newL->filial3[mes].facturado += (valor*uni);
                    newL->filial3[mes].total += uni;
                } else {
                    newL->filial3[mes].P += uni;
                    newL->filial3[mes].facturado += (valor*uni);
                    newL->filial3[mes].total += uni;
                }
                    newL->total += uni;
                    old->total[mes][3] += uni;
                break;
            }
            newL->next = old->lProdsFil.lista->next;
            old->lProdsFil.lista = newL;
            
            avl_insert(old->lProdsFil.tree, newL);
            //printf("%s\n", newL->cod);
        }
        
    }
    return fil;
}

Filial instert_clientesFil(Filial fil, char* cod){
    LFilial *novo = (LFilial*) malloc(sizeof (LFilial));
    TFilial *tree;
    LProdF *list;
    
    tree = avl_create(compare_strings4, NULL, NULL);
    list = (LProdF*) malloc(sizeof (LProdF));    
        
    
    int i = 0;
    novo->cod = (char*) malloc(sizeof (cod));
    strcpy(novo->cod, cod);
    for (i = 1; i <= 12; i++) {
        novo->total[i][1] = 0;
        novo->total[i][2] = 0;
        novo->total[i][3] = 0;
    }
    
    novo->lProdsFil.lista = list;
    novo->lProdsFil.tree = tree;
    
    
    novo->next = fil->lista;
    fil->lista = novo;

    avl_insert(fil->tree, novo);
    
    return fil;
}

Filial criar_filial() {
    TFilial *tree;
    LFilial *list;
    Filial filial;
    
    tree = avl_create(compare_strings4, NULL, NULL);
    list = (LFilial*) malloc(sizeof (LFilial));    

    filial = (Filial*) malloc(sizeof (Filial));

    filial->lista = list;
    filial->tree = tree;
    

    return filial;
}