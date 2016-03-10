#include "avl.h"
#include "CatC.h"
#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 8192

int
compare_ints (const void *pa, const void *pb, void *param)
{
  const int *a = pa;
  const int *b = pb;

  if (*a < *b)
    return -1;
  else if (*a > *b)
    return +1;
  else
    return 0;
}

int compare_strings (const void *pa, const void *pb){
    const char **a = pa;
    const char **b = pb;
    
    return strcmp(*a, *b);
}

print_tree_structure (const struct avl_node *node, int level)
{
  /* You can set the maximum level as high as you like.
     Most of the time, you'll want to debug code using small trees,
     so that a large |level| indicates a ``loop'', which is a bug. */
  if (level > 16)
    {
      printf ("[...]");
      return;
    }

  if (node == NULL)
    return;

  printf ("%s", *(int *) node->avl_data);
  if (node->avl_link[0] != NULL || node->avl_link[1] != NULL)
    {
      putchar ('(');

      print_tree_structure (node->avl_link[0], level + 1);
      if (node->avl_link[1] != NULL)
        {
          putchar (',');
          print_tree_structure (node->avl_link[1], level + 1);
        }

      putchar (')');
    }
}


void
print_whole_tree (const struct avl_table *tree, const char *title)
{
  printf ("%s: ", title);
  print_tree_structure (tree->avl_root, 0);
  putchar ('\n');
}

Clientes *criar_clientes(){
    TClientes *tree;   
    LClientes *list;    
    Clientes *clientes;
    
    tree = avl_create (compare_strings, NULL, NULL);
    list = (LClientes*) malloc(sizeof(LClientes));
    list = NULL;
    clientes = (Clientes*) malloc(sizeof(Clientes));
    
    clientes->lista = list;
    clientes->tree = tree;
    
    return clientes;
}

void *insert_clientes (Clientes *clientes, char* st){
    LClientes *cliente = (LClientes*) malloc(sizeof(clientes->lista));
    cliente->cod =(char*) malloc(sizeof(st));    
    
    strcpy(cliente->cod, st);
    cliente->next = clientes->lista;
    clientes->lista = cliente;
    
    avl_insert(clientes->tree, &cliente->cod); 
            
    
    return NULL;
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
