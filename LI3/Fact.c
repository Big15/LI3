#include "Fact.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_FACT 100000

typedef struct avl_table TFact;

typedef struct InfFact {
    float total;
    float fN;
    float fP;
    int uni;
    int N;
    int P;
} InfFact;

typedef struct LFact {
    char* cod;
    int vt1;
    int vt2;
    int vt3;
    InfFact filial1[13];
    InfFact filial2[13];
    InfFact filial3[13];
    struct LFact *next;
} LFact;

typedef struct EFact {
    TFact *tree;
    LFact *lista;
} EFact;

typedef struct Q10s {
    char* cod;
    int vendas[4];    
    struct Q10s *next;
} Q10s;

int compare_strings3(const void *pa, const void *pb) {
    const LFact *a = pa;

    const LFact *b = pb;

    return strcmp(a->cod, b->cod);
}

int travessia_tree_q4(const struct avl_node *node, int n, List list, int tipo) {    
    LFact *old = node->avl_data;
    if (node->avl_link[0] != NULL){
        n = travessia_tree_q4(node->avl_link[0], n, list, tipo);
    }
    switch(tipo){
        case 0:
        if(old->vt1 == 0 && old->vt2 == 0 && old->vt3 == 0){
            list = add_string_l(list, old->cod);
            n++;
        }
        break;
        case 1:
        if(old->vt1 == 0){
            list = add_string_l(list, old->cod);
            n++;
        }
        break;
        case 2:
        if(old->vt2 == 0){
            list = add_string_l(list, old->cod);
            n++;
        }
        break;
        case 3:
        if(old->vt3 == 0){
            list = add_string_l(list, old->cod);
            n++;
        }
        break;
    }
    if(node->avl_link[1] != NULL){
        n = travessia_tree_q4(node->avl_link[1], n, list, tipo);
    }    
    
    return n;
}

List q3(Fact fact, List list, int mes, char* cod, int tipo){
    int n;
    char* res = (char*) malloc(sizeof(char*)*50);
    LFact *novo = (LFact*) malloc(sizeof (LFact));
    novo->cod = strdup(cod);
    novo = avl_find(fact->tree, novo);
    
    if(novo != NULL){
        switch(tipo){
            case 0:
                sprintf(res, "N:%d", ((novo->filial1[mes].N)+(novo->filial2[mes].N)+(novo->filial3[mes].N)));
                list = add_string_l(list, res);
                sprintf(res, "P:%d", ((novo->filial1[mes].P)+(novo->filial2[mes].P)+(novo->filial3[mes].P)));               
                list = add_string_l(list, res);
                sprintf(res, "fN:%.3f", ((novo->filial1[mes].fN)+(novo->filial2[mes].fN)+(novo->filial3[mes].fN)));
                list = add_string_l(list, res);
                sprintf(res, "fP:%.3f", ((novo->filial1[mes].fP)+(novo->filial2[mes].fP)+(novo->filial3[mes].fP)));
                list = add_string_l(list, res);
                sprintf(res, "fT:%.3f", ((novo->filial1[mes].total)+(novo->filial2[mes].total)+(novo->filial3[mes].total)));
                list = add_string_l(list, res);
                
            break;
            case 1:
                sprintf(res, "N:%d", (novo->filial1[mes].N));
                list = add_string_l(list, res);
                sprintf(res, "P:%d", (novo->filial1[mes].P));               
                list = add_string_l(list, res);
                sprintf(res, "fN:%.3f", (novo->filial1[mes].fN));
                list = add_string_l(list, res);
                sprintf(res, "fP:%.3f", (novo->filial1[mes].fP));
                list = add_string_l(list, res);
                sprintf(res, "fT:%.3f", (novo->filial1[mes].total));
                list = add_string_l(list, res);
            break;
            case 2:
                sprintf(res, "N:%d", (novo->filial2[mes].N));
                list = add_string_l(list, res);
                sprintf(res, "P:%d", (novo->filial2[mes].P));               
                list = add_string_l(list, res);
                sprintf(res, "fN:%.3f", (novo->filial2[mes].fN));
                list = add_string_l(list, res);
                sprintf(res, "fP:%.3f", (novo->filial2[mes].fP));
                list = add_string_l(list, res);
                sprintf(res, "fT:%.3f", (novo->filial2[mes].total));
                list = add_string_l(list, res);
            break;
            case 3:
                sprintf(res, "N:%d", (novo->filial3[mes].N));
                list = add_string_l(list, res);
                sprintf(res, "P:%d", (novo->filial3[mes].P));               
                list = add_string_l(list, res);
                sprintf(res, "fN:%.3f", (novo->filial3[mes].fN));
                list = add_string_l(list, res);
                sprintf(res, "fP:%.3f", (novo->filial3[mes].fP));
                list = add_string_l(list, res);
                sprintf(res, "fT:%.3f", (novo->filial3[mes].total));
                list = add_string_l(list, res);
            break;                
        }
    }
        
}

List q4(Fact fact, List list, int tipo){
    int n;
    n = travessia_tree_q4(fact->tree->avl_root, 0, list, tipo);
    
    
    return list;
}

int travessia_tree_q12(const struct avl_node *node, int n) {    
    LFact *old = node->avl_data;
    if (node->avl_link[0] != NULL) {
        n = travessia_tree_q12(node->avl_link[0], n);
    }

    if (old->vt1 == 0 && old->vt2 == 0 && old->vt3 == 0) {
        n++;
    }

    if (node->avl_link[1] != NULL){
        n = travessia_tree_q12(node->avl_link[1], n);
    }    
    
    return n;
}

List q12_fact(Fact fact, List list){
    int n;
    char* res = (char*) malloc (sizeof(char*)*30);
    n = travessia_tree_q12(fact->tree->avl_root, 0);
    sprintf(res, "Produtos nunca foram comprados: %d", n);
    list = add_string_l(list, res);    
    
    return list;
}

int travessia_tree_q6_uni(const struct avl_node *node, int mes1, int mes2) {
    int n = 0, i;
    LFact *old = node->avl_data;
    if (node->avl_link[0] != NULL){
        n += travessia_tree_q6_uni(node->avl_link[0], mes1, mes2);
    }
    
    for(i = mes1; i <= mes2; i++){
        n += old->filial1[i].uni;
        n += old->filial2[i].uni;
        n += old->filial3[i].uni;
    }
    
    if(node->avl_link[1] != NULL){
        n += travessia_tree_q6_uni(node->avl_link[1], mes1, mes2);
    }    
    
    return n;
}

float travessia_tree_q6_fact(const struct avl_node *node, int mes1, int mes2) {
    int i;
    float n = 0;
    LFact *old = node->avl_data;
    if (node->avl_link[0] != NULL){
        n += travessia_tree_q6_fact(node->avl_link[0], mes1, mes2);
    }
    
    for(i = mes1; i <= mes2; i++){
        n += old->filial1[i].total;
        n += old->filial2[i].total;
        n += old->filial3[i].total;
    }    
    
    if(node->avl_link[1] != NULL){
        n += travessia_tree_q6_fact(node->avl_link[1], mes1, mes2);
    }    
    
    return n;
}

List q6(Fact fact, List list, int mes1, int mes2){
    int uni = 0;
    float fp = 0;    
    char* res = (char*) malloc(sizeof(char*)*50);
    
    uni = travessia_tree_q6_uni(fact->tree->avl_root, mes1, mes2);
    
    fp = travessia_tree_q6_fact(fact->tree->avl_root, mes1, mes2);
    
    sprintf(res, "FACTURADO TOTAL = %.0f", fp);
    list = add_string_l(list, res);
    sprintf(res, "UNIDADES VENDIDAS = %d", uni);
    list = add_string_l(list, res);
    
    return list;
    
}

InfFact novo_filial_fact() {
    InfFact novo;
    novo.N = 0;
    novo.P = 0;
    novo.fN = 0;
    novo.fP = 0;
    novo.total = 0;
    novo.uni = 0;

    return novo;
}

Q10s* q10_add_list(Q10s* res, char* cod, int n, int t, int n1, int n2, int n3){
    Q10s *aux = res;
    Q10s *prev;
    Q10s *novo = (Q10s*) malloc(sizeof(Q10s));    
    int count = 0, flag = 1; 
    while(aux != NULL && count < t && flag){
        if(aux->vendas[0] < n){
            novo->cod = strdup(cod);
            novo->vendas[0] = n;
            novo->vendas[1] = n1;
            novo->vendas[2] = n2;
            novo->vendas[3] = n3;
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
    if(count < t && flag){
        novo->cod = strdup(cod);
        novo->vendas[0] = n;
        novo->vendas[1] = n1;
        novo->vendas[2] = n2;
        novo->vendas[3] = n3;
        aux = novo;
    }
    return res;
}

Q10s* travessia_tree_q10_fact(const struct avl_node *node, Q10s* res, int n) {
    int i;
    int t = 0;
    LFact *old = node->avl_data;
    if (node->avl_link[0] != NULL){
        res = travessia_tree_q10_fact(node->avl_link[0], res, n);
    }
    
    t = old->vt1 + old->vt2 + old->vt3;
    res = q10_add_list(res, old->cod, t, n, old->vt1, old->vt2, old->vt3);
    
        
    if(node->avl_link[1] != NULL){
        res = travessia_tree_q10_fact(node->avl_link[1], res, n);
    }    
    
    return res;
}

List q10_fact(Fact fact, List list, int n){
    int i = 0;
    char* aux = (char*) malloc (sizeof(char*)*30);
    Q10s *res = (Q10s*) malloc(sizeof(Q10s));
    res = travessia_tree_q10_fact(fact->tree->avl_root, res, n);
    
    while(res != NULL && i < n){
        list = add_string_l(list, res->cod);
        sprintf(aux, "%d - %d - %d - %d", res->vendas[0], res->vendas[1], res->vendas[2], res->vendas[3]);
        list = add_string_l(list, aux);
        //printf("%s - %d - %d - %d - %d\n", res->cod, res->vendas[0], res->vendas[1], res->vendas[2], res->vendas[3]);
        res = res->next;
        i++;
    }
    
    return list;
}

Fact insert_vendasF(Fact fact, char* prod, float valor, int uni, char* promo, int mes, int filial) {

    LFact *novo = (LFact*) malloc(sizeof (LFact));
    LFact *old;
    novo->cod = (char*) malloc(sizeof (prod));
    strcpy(novo->cod, prod);

    old = avl_find(fact->tree, novo);

    if (old != NULL)
        switch (filial) {
            case 1:
                if (!strcmp(promo, "N")) {
                    old->filial1[mes].N += uni;
                    old->filial1[mes].fN += (valor*uni);
                    old->filial1[mes].total += (valor*uni);
                    old->filial1[mes].uni += uni;
                } else {
                    old->filial1[mes].P += uni;
                    old->filial1[mes].fP += (valor*uni);
                    old->filial1[mes].total += (valor*uni);
                    old->filial1[mes].uni += uni;
                }
                old->vt1 += uni;
                break;
            case 2:
                if (!strcmp(promo, "N")) {
                    old->filial2[mes].N += uni;
                    old->filial2[mes].fN += (valor*uni);
                    old->filial2[mes].total += (valor*uni);
                    old->filial2[mes].uni += uni;
                } else {
                    old->filial2[mes].P += uni;
                    old->filial2[mes].fP += (valor*uni);
                    old->filial2[mes].total += (valor*uni);
                    old->filial2[mes].uni += uni;
                }
                old->vt2 += uni;
                break;
            case 3:
                if (!strcmp(promo, "N")) {
                    old->filial3[mes].N += uni;
                    old->filial3[mes].fN += (valor*uni);
                    old->filial3[mes].total += (valor*uni);
                    old->filial3[mes].uni += uni;
                } else {
                    old->filial3[mes].P += uni;
                    old->filial3[mes].fP += (valor*uni);
                    old->filial3[mes].total += (valor*uni);
                    old->filial3[mes].uni += uni;
                }
                old->vt3 += uni;
                break;
        }
        

    return fact;

}



Fact insert_produtosF(Fact fact, char* prod) {
    LFact *novo = (LFact*) malloc(sizeof (LFact));
    int i = 0;
    novo->cod = (char*) malloc(sizeof (prod));

    strcpy(novo->cod, prod);
    for(i = 0; i<= 12; i++){
        novo->filial1[i] = novo_filial_fact();
        novo->filial2[i] = novo_filial_fact();
        novo->filial3[i] = novo_filial_fact();
    }
    novo->vt1 = 0;
    novo->vt2 = 0;
    novo->vt3 = 0;
    novo->next = fact->lista;
    fact->lista = novo;

    avl_insert(fact->tree, novo);

    return fact;
}

void teste(Fact fact, char* prod) {
    LFact *novo = (LFact*) malloc(sizeof (LFact));
    LFact *old;
    novo->cod = (char*) malloc(sizeof (prod));
    strcpy(novo->cod, prod);

    old = avl_find(fact->tree, novo);
    
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