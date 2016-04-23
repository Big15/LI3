#include "Codigo.h"

typedef struct cod {
    char* cod;    
}cod;

char* get_codigo(Codigo cod){
    return cod->cod;
}

Codigo set_codigo(Codigo cod, char* s){   
    cod->cod = (char*) malloc(sizeof (s));
    cod->cod = strdup(s);
    return cod;
}
