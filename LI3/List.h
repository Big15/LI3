#ifndef LIST_H
#define LIST_H

typedef struct lst* List;

List add_string_l(List l, char* s);

char* get_string_l(List l, int n);

int get_np_l(List l);

List novo_l();


#endif
