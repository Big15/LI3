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
    const char *a;
    strcpy(a, pa);
    const char *b;
    strcpy(b, pb);
    
    return strcmp(a, b);
}

int compare_strings2 (char *pa, char *pb){
    
    return strcmp(pa, pb);
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
    Clientes *tree;    
    
    tree = avl_create (compare_ints, NULL, NULL);
    
    return tree;
}

void *insert_clientes (Clientes *tree, char** st){
    //char* cod;    
    //printf("%s\n", *st);
    avl_insert(tree, st); 
    
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
