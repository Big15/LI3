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

typedef struct Q9s {
    char* cod;
    int vendas;    
    struct Q9s *next;
} Q9s;


int compare_strings4(const void *pa, const void *pb) {
    const LFilial *a = pa;

    const LFilial *b = pb;

    return strcmp(a->cod, b->cod);
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
        }
        if(p){
            concat_string_l(list, old->cod, 1);
            concat_string_l(list, " ", 1);
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
    char* aux = (char*) malloc (sizeof(char*)*100);
    int n = travessia_tree_q7(fil->tree->avl_root);
    sprintf(aux, "%d clientes que compraram em todas as filiais", n);
    add_string_l(list, aux);
    return list;
}


List q5(Filial fil, List list, char* cod){
    LFilial *novo = (LFilial*) malloc(sizeof (LFilial)); 
    LFilial *old;
    char* aux = (char*) malloc (sizeof(char*)*100);
    int i;
    
    novo->cod = (char*) malloc(sizeof (cod));
    strcpy(novo->cod, cod); 
    
    old = avl_find(fil->tree, novo);
    
    if(old != NULL){
        sprintf(aux, "Mes   Filial1   Filial2     Filial3");
        list = add_string_l(list, aux);
        for(i = 1; i <= 12; i++){
            sprintf(aux, "%d      %d          %d          %d", i, old->total[i][1], old->total[i][2], old->total[i][3]);
            list = add_string_l(list, aux);
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
            n++;
        }

    if (node->avl_link[1] != NULL){
        n = travessia_tree_q12_fili(node->avl_link[1], n);
    }    
    
    return n;
}

int travessia_tree_q10_fili(const struct avl_node *node, int n, char* cod) {    
    LFilial *old = node->avl_data; 
    LProdF *prods = (LProdF*) malloc(sizeof(LProdF));
    prods->cod = strdup(cod);
    int i, n1 = 0, n2 = 0, n3 = 0;
    if (node->avl_link[0] != NULL) {
        n = travessia_tree_q10_fili(node->avl_link[0], n, cod);
    }
    
    if(avl_find(old->lProdsFil.tree, prods))
        n++;

    if (node->avl_link[1] != NULL){
        n = travessia_tree_q10_fili(node->avl_link[1], n, cod);
    }    
    
    return n;
}

Q9s* add_q9s(Q9s* res, char* cod, int n){
    Q9s *aux = res;
    Q9s *prev;
    Q9s *novo = (Q9s*) malloc(sizeof(Q9s));    
    int count = 0, flag = 1; 
    while(aux != NULL && flag){
        if(aux->vendas < n){
            novo->cod = strdup(cod);
            
            novo->vendas = n;            
            if(count == 0){
                novo->next = res;
                res = novo;
            }
            else{
                novo->next = aux;
                prev->next = novo;
            }
            flag = 0;
        }
        prev = aux;
        aux = aux->next;
        count++;
    }
    if(flag){
        novo->cod = strdup(cod);
        novo->vendas = n;        
        aux = novo;
    }
    return res;
}

Q9s* travessia_tree_q9(const struct avl_node *node, Q9s* res, int mes) {    
    LProdF *old = node->avl_data; 
    
    int i, n1 = 0, n2 = 0, n3 = 0;
    if (node->avl_link[0] != NULL) {
        res = travessia_tree_q9(node->avl_link[0], res, mes);
    }
    
    res = add_q9s(res, old->cod, ((old->filial1[mes].total)+(old->filial2[mes].total)+(old->filial3[mes].total)));

    if (node->avl_link[1] != NULL){
        res = travessia_tree_q9(node->avl_link[1], res, mes);
    }    
    
    return res;
}

List q9(Filial fil, List list, char* cli, int mes){
    LFilial *novo = (LFilial*) malloc(sizeof (LFilial));
    LFilial *old;
    Q9s *res = (Q9s*) malloc(sizeof(Q9s));
    char* aux = (char*) malloc (sizeof(char*)*30);
    
    novo->cod = (char*) malloc(sizeof (cli));
    strcpy(novo->cod, cli);  
    
    old = avl_find(fil->tree, novo);
    if(old != NULL){
        res = travessia_tree_q9(old->lProdsFil.tree->avl_root, res, mes);  
    }
    while(res != NULL && res->cod != NULL){
        sprintf(aux, "%s - %d", res->cod, res->vendas);
        list = add_string_l(list, aux);
        res = res->next;
    }
    return list;
}

Q9s* add_q11s(Q9s* res, char* cod, int n){
    Q9s *aux = res;
    Q9s *prev;
    Q9s *novo = (Q9s*) malloc(sizeof(Q9s));    
    int count = 0, flag = 1; 
    while(aux != NULL && flag){
        if(aux->vendas < n){
            novo->cod = strdup(cod);
            
            novo->vendas = n;            
            if(count == 0){
                novo->next = res;
                res = novo;
            }
            else{
                novo->next = aux;
                prev->next = novo;
            }
            flag = 0;
        }
        prev = aux;
        aux = aux->next;
        count++;
    }
    if(flag){
        novo->cod = strdup(cod);
        novo->vendas = n;        
        aux = novo;
    }
    return res;
}

Q9s* travessia_tree_q11(const struct avl_node *node, Q9s* res) {    
    LProdF *old = node->avl_data; 
    int n = 0, i;
    if (node->avl_link[0] != NULL) {
        res = travessia_tree_q11(node->avl_link[0], res);
    }
    for(i = 1; i <= 12; i++){
        n += old->filial1[i].facturado;
        n += old->filial2[i].facturado;
        n += old->filial3[i].facturado;
    }
    
    res = add_q9s(res, old->cod, n);

    if (node->avl_link[1] != NULL){
        res = travessia_tree_q11(node->avl_link[1], res);
    }    
    
    return res;
}

List q11(Filial fil, List list, char* cli){
    LFilial *novo = (LFilial*) malloc(sizeof (LFilial));
    LFilial *old;
    int i = 0;
    Q9s *res = (Q9s*) malloc(sizeof(Q9s));
    char* aux = (char*) malloc (sizeof(char*)*30);
    
    novo->cod = (char*) malloc(sizeof (cli));
    strcpy(novo->cod, cli);  
    
    old = avl_find(fil->tree, novo);
    if(old != NULL){
        res = travessia_tree_q11(old->lProdsFil.tree->avl_root, res);  
    }
    while(res != NULL && res->cod != NULL && i < 3){
        sprintf(aux, "%s - %d", res->cod, res->vendas);
        list = add_string_l(list, aux);
        res = res->next;
        i++;
    }
    return list;
}

List q10_fili(Filial fil, List l, int t){
    int i, n;
    char* aux = (char*) malloc (sizeof(char*)*10);
    for(i=0; i<get_np_l(l); i+=2){
        n = travessia_tree_q10_fili(fil->tree->avl_root, 0, get_string_l(l, i));
        sprintf(aux, " - %d", n);
        l = concat_string_l(l, aux, i+1);
    }
    return l;
    
}

List q12_fili(Filial fil, List list, int t){
    int n;
    char* res = (char*) malloc (sizeof(char*)*30);
    n = travessia_tree_q10_fili(fil->tree->avl_root, list, t);
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