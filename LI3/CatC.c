#include "CatC.h"
#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 8192
#define MAX_CLIENTES 20000

typedef struct avl_table TClientes;

typedef struct LClientes{
    char* cod;
    struct LClientes *next;    
}LClientes;

typedef struct CClientes{
    TClientes *tree;
    LClientes *lista;
}CClientes;

typedef struct ListClientes{
    char* cliente[MAX_CLIENTES];
    int nclientes;
};

int compare_strings (const void *pa, const void *pb){
    const char **a = pa;
    const char **b = pb;
    
    return strcmp(*a, *b);
}

/*
print_tree_structure(const struct avl_node *node, int level) {
    /* You can set the maximum level as high as you like.
       Most of the time, you'll want to debug code using small trees,
       so that a large |level| indicates a ``loop'', which is a bug. 
    if (level > 16) {
        printf("[...]");
        return;
    }

    if (node == NULL)
        return;

    printf("%s", *(int *) node->avl_data);
    if (node->avl_link[0] != NULL || node->avl_link[1] != NULL) {
        putchar('(');

        print_tree_structure(node->avl_link[0], level + 1);
        if (node->avl_link[1] != NULL) {
            putchar(',');
            print_tree_structure(node->avl_link[1], level + 1);
        }

        putchar(')');
    }
}
/*
void print_whole_tree(const struct avl_table *tree, const char *title) {
    printf("%s: ", title);
    print_tree_structure(tree->avl_root, 0);
    putchar('\n');
}

void *print(Clientes clientes){
    print_whole_tree(clientes->tree, "Cenas");
}
*/

int travessia_tree_structure(const struct avl_node *node, int n, LstClientes* clientes) {    
    
    if (node->avl_link[0] != NULL){
        n = travessia_tree_structure(node->avl_link[0], n, clientes);
    }
        (*clientes)->cliente[n] = strdup( *(int*) node->avl_data);
        //if(n < 20)  printf("%s - %d\n", (*clientes)->cliente[n], n);
        n++;
    if(node->avl_link[1] != NULL){
        n = travessia_tree_structure(node->avl_link[1], n, clientes);
    }    
    
    return n;
}



LstClientes cria_lclientes(Clientes clientes){
    LstClientes novo = (LstClientes*) malloc(sizeof(LstClientes) * MAX_CLIENTES);
    int n;
    n = travessia_tree_structure(clientes->tree->avl_root, 0, &novo);
    novo->nclientes = n;
    
    return novo;
}

int check_cliente(Clientes cli, char* cod){
    int n;
    LClientes *novo = (LClientes*) malloc(sizeof (LClientes));
    novo->cod = strdup(cod);
    novo = avl_find(cli->tree, novo);
    
    if(novo == NULL)
        n = 1;
    else
        n = 0;
    return n;
}

Clientes criar_clientes(){
    TClientes *tree;   
    LClientes *list;    
    Clientes clientes;
    
    tree = avl_create (compare_strings, NULL, NULL);
    list = (LClientes*) malloc(sizeof(LClientes));
    list = NULL;
    clientes = (Clientes*) malloc(sizeof(Clientes));
    
    clientes->lista = list;
    clientes->tree = tree;
    
    return clientes;
}

Clientes insert_clientes (Clientes clientes, char* st){
    LClientes *cliente = (LClientes*) malloc(sizeof(clientes->lista));
    cliente->cod =(char*) malloc(sizeof(st));    
    
    strcpy(cliente->cod, st);
    cliente->next = clientes->lista;
    clientes->lista = cliente;
    
    avl_insert(clientes->tree, &cliente->cod); 
            
    
    return clientes;
}

/*int main(void) {

		struct avl_table *tree;
		int i[10];
		int j;
		for(j=0; j<10; j++){
			i[j]=j;
		}

		struct libavl_allocator *allocator = &avl_allocator_default;

		tree = avl_create (compare_ints, NULL, allocator);

		for(j=0; j<10; j++){
			avl_insert(tree, &i[j]);
		}		



		print_whole_tree(tree, "Cenas");

		//printf("N: %d\n", tree->avl_count);

		printf("END!!");
	}*/
