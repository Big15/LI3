#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "CatC.h"
#include "CatP.h"
#include "Fact.h"

void *ler_clientes(Clientes CC, char *filename) {
    int X = 10, i = 0, flag = 0, lidos = 0;
    char s[10];
    char* cod;
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        while (fgets(s, X, f)) {
            cod = strtok(s, "\r\n");
            insert_clientes(CC, cod);
            cod = (char*) malloc(10);
            lidos++;
        }
    }

    printf("Clientes lidos: %d\n", lidos);
    return NULL;
}

void *ler_produtos(Produtos CP, char * filename) {
    int X = 10, i = 0, flag = 0, lidos = 0;
    char s[10];
    char* cod;
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        while (fgets(s, X, f)) {
            cod = strtok(s, "\r\n");
            insert_produtos(CP, cod);
            cod = (char*) malloc(10);
            lidos++;
        }
    }

    printf("Produtos lidos: %d\n", lidos);
    return NULL;
}

/*int ler_vendas(char * filename) {
    int X = 100, i = 0, lidos = 0, unidades = 0, mes = 0, filial =0;	//Necessário verificar se codigo de Prod e de Cliente
    float valor;
    char s[100];
    char codProd[10];
    char* linha;
    char codCliente[10];
    char promo[3];
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        while (fgets(s, X, f)) {
            linha = strtok(s, " ");
            i = 0;
            while (linha != NULL) {
                switch (i) {
                    case 0: strcpy(codProd, linha);
                        break;
                    case 1: valor = atof(linha);
                        break;
                    case 2: unidades = atoi(linha);
                        break;
                    case 3: strcpy(promo, linha);
                        break;
                    case 4: strcpy(codCliente, linha);
                        break;
                    case 5: mes = atoi(linha);
                        break;
                    case 6: filial = atoi(linha);
                        break;
                }
                i++;
                linha = strtok(NULL, " ");
            }
            
            lidos++;
        }
    }
    printf("Vendas registadas: %d\n", lidos);
    return 1;
}*/


int main() {
    Clientes CClientes;
    Produtos CProdutos;
    Fact fact;

    CClientes = criar_clientes();
    CProdutos = criar_produtos();
    fact = criar_fact();

    ler_clientes(CClientes, "Clientes.txt");
    ler_produtos(CProdutos, "Produtos.txt");
    //ler_vendas("Vendas_1M.txt");                  

    print(CClientes);
    //print_whole_tree(CClientes->tree, "Cenas");
    
    // printf("%s\n", CClientes->lista->cod);

    // print_whole_tree(CProdutos->tree, "Cenas");
    // printf("%s\n", CProdutos->lista->cod);
    // printf("AVL Clientes: %d\nAVL Produtos: %d\n",(int) CClientes->tree->avl_count, (int) CProdutos->tree->avl_count);
    printf("END\n");
    return 0;
}