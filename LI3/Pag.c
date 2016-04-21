#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Pag.h"

typedef struct pag {
    List pag;
    int n; //n elementos por página 
    int p; // pagina actual
};

int getElems(Page pagina, Page novo) {

    novo->n = pagina->n;
    return novo;
}

Page cria_Pagina(List l, int a, int b) {
    Page pagina = (Page*) malloc(sizeof (Page));
    pagina->pag = l;
    pagina->n = a;
    pagina->p = b;
    return pagina;


}

Page getNextString(Page pagina, Page novo) {
    char** str;
    int c = novo->n;
    novo->pag = pagina->pag;
    str[c] = get_string_l(novo->pag, c);
    return str[c];

}

int getPag(Page pagina, Page novo) {
    novo->p = pagina->p;
    return novo;
}

Page next_Page(Page pagina, Page novo) {

    novo->pag = pagina->pag;
    novo->n = pagina->n;
    novo->p = pagina->p;

    int i;


    for (i = 0; i < getPag(pagina, novo); i++) {
        novo = getNextString(pagina, novo);



    }
    return novo;
}



