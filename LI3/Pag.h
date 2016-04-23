#ifndef PAG_H
#define PAG_H

typedef struct pag* Page;

int getElems (Page pagina, Page novo);
Page cria_Pagina(List l, int n, int p);
char* getNextString(Page pagina, Page novo);
Page next_Page(Page pagina, Page novo);
int getPag(Page pagina, Page novo);

#endif