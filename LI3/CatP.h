#include "avl.h"

typedef struct avl_table TProdutos;

typedef struct LProdutos {
    char* cod;
    struct LProdutos *next;
} LProdutos;

typedef struct Produtos {
    TProdutos *tree;
    LProdutos *lista;
} Produtos;

