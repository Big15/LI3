#include "avl.h"
#include "List.h"

typedef struct EFact* Fact;

typedef struct ListFact* LstFact;

Fact criar_fact();

Fact insert_produtosF(Fact fact,char* prod);

Fact insert_vendasF(Fact fact, char* prod, float valor, int uni, char* promo, int mes, int filial);

void teste(Fact fact, char* prod);

List q3(Fact fact, List list, int mes, char* cod, int tipo);

List q4(Fact fact, List list, int tipo);