#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "CatC.h"


void *ler_clientes(Clientes *CC, char *filename) {
    int X = 10, i = 0, flag = 0, lidos = 0, falhas = 0;
    char s[10];
    char* cod;
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        while (fgets(s, X, f)) {
            cod = strtok(s, "\r\n");
            insert_clientes(CC, &cod);
            cod = (char*) malloc (10);
            lidos++;
        }        
    }

    printf("Clientes lidos: %d\n", lidos);
    return NULL;
}

int ler_produtos(char * filename) {
    int X = 10, i = 0, flag = 0, lidos = 0, falhas = 0;
    char s[10];
    char* codProd;
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        while (fgets(s, X, f)) {
            codProd = strtok(s, "\r\n");            
            lidos++;
        }        
    }
    
    printf("Produtos lidos: %d\n", lidos);
    return 1;
}

int ler_vendas(char * filename) {
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
}


int main() {	
        Clientes *CClientes;
        
        CClientes = criar_clientes();
        
	ler_clientes(CClientes, "Clientes.txt");
	ler_produtos("Produtos.txt");
	ler_vendas("Vendas_1M.txt");                  
        
        /*char* aux = "BLAH!";
        insert_clientes(CClientes, &aux);*/
        
        //print_whole_tree(CClientes, "Cenas");
        printf("N: %d\n", CClientes->avl_count);
        printf("END\n");
        return 0;
	}



