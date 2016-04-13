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
};

typedef char* Cliente;

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

LstClientes travessia_tree_structure(const struct avl_node *node, int n, LstClientes clientes) { 
   
    if (node->avl_link[0] != NULL){
        n = travessia_tree_structure(node->avl_link[0], n, clientes);
        clientes->cliente[n] = strdup( *(int*) node->avl_data);
        if(n < 10)  printf("%s - %d\n", clientes->cliente[n], n);
        n++;
        if(node->avl_link[1] != NULL){
            n = travessia_tree_structure(node->avl_link[1], n, clientes);
            clientes->cliente[n] = strdup( *(int*) node->avl_data);
            if(n < 10)  printf("%s - %d\n", clientes->cliente[n], n);
            n++;
        }
    }
    
    
    return clientes;
        
        /*
        || node->avl_link[1] != NULL) {

        n = travessia_tree_structure(node->avl_link[0], n, clientes);        
        //if(n<100)    printf("%d - %s - %s\n", n, *(int*) node->avl_data, clientes->cliente[n]);
        //n++;
        if (node->avl_link[1] != NULL) {
            n = travessia_tree_structure(node->avl_link[1], n, clientes);
        }
        clientes->cliente[n] = strdup( *(int*) node->avl_data);
        n++;
        return n;
    }
    return n;*/
}

print_clientes(LstClientes l){
    int i;
    for(i = 0; i < 10; i++)
        printf("%s\n", l->cliente[i]);
}

LstClientes cria_lclientes(Clientes clientes){
    LstClientes novo = (LstClientes*) malloc(sizeof(LstClientes));
    int n;
    novo = travessia_tree_structure(clientes->tree->avl_root, 0, novo);
    printf("%d - %s\n", n, novo->cliente[0]);
    return novo;
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
