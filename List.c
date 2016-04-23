#include "List.h"

typedef struct lst{
    char** string;
    int n;
};

char* get_string_l(List l, int n){
    return l->string[n];
}

int get_np_l(List l){
    int n = l->n ;
    return n;
}

List concat_string_l(List l, char* s, int i){
    int n = l->n;
    strcat(l->string[i], s);

    return l;
}

List add_string_l(List l, char* s){
    int n = l->n;
    l->string = (char**) realloc(l->string, (n+1) * sizeof(char*));
    l->string[n] = strdup(s);
    l->n++;

    return l;
}

List novo_l(){
    List novo = (List*) malloc(sizeof(List));
    novo->string = (char**) malloc(sizeof(char*));
    novo->n = 0;
    
    return novo;
}

List clear_l(List lista){
    lista->n=0;
    free(lista->string);
    
    return lista;
}