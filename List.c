#include "List.h"

#define MAX 1000000

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

List add_string_lt(List l, char* s){
    int n = l->n;
    //malloc(auxlista->size x sizeof (char*))
    l->string[n] = malloc(l->n * sizeof(s));
    strcpy(l->string[l->n], s);
    l->n++;    
    return l;
}

List add_string_l(List l, char* s){
    int n = l->n;
    //malloc(auxlista->size x sizeof (char*))
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
