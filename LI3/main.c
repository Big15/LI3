#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "CatC.h"
#include "CatP.h"
#include "Fact.h"


void *ler_clientes(Clientes cC, char *filename) {
    int X = 10, i = 0, flag = 0, lidos = 0;
    char s[10];
    char* cod;
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        while (fgets(s, X, f)) {
            cod = strtok(s, "\r\n");
            cC = insert_clientes(cC, cod);
            cod = (char*) malloc(10);
            lidos++;
        }
    }

    printf("Clientes lidos: %d\n", lidos);
    return NULL;
}

void *ler_produtos(Produtos cP, Fact fact, char * filename) {
    int X = 10, i = 0, flag = 0, lidos = 0;
    char s[10];
    char* cod;
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        while (fgets(s, X, f)) {
            cod = strtok(s, "\r\n");
            cP = insert_produtos(cP, cod);
            fact = insert_produtosF(fact,cod);
            cod = (char*) malloc(10);
            lidos++;
        }
    }

    printf("Produtos lidos: %d\n", lidos);
    return NULL;
}

int ler_vendas(Fact fact, Clientes cC, Produtos cP, char * filename) {
    int X = 100, i = 0, lidos = 0, unidades = 0, mes = 0, filial =0;	//Necessário verificar se codigo de Prod e de Cliente
    int cfalha = 0, pfalha = 0, certos = 0, falhas = 0;
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
            cfalha += check_cliente(cC, codCliente);
            pfalha += check_produto(cP, codProd);
            if(!check_produto(cP, codProd) && !check_cliente(cC, codCliente)){
                fact = insert_vendasF(fact, codProd, valor, unidades, promo, mes, filial);
                certos++;
            }
            else
                falhas++;
            lidos++;
        }
    }
    printf("Vendas registadas: %d\n", lidos);
    printf("Vendas com codigos de cliente errados: %d\n", cfalha);
    printf("Vendas validas: %d\n", certos);
    printf("Invalidas: %d\n", falhas);
    return 1;
}

void travessia(List list){
    int n = 1, i = 0, p = 0, max;    
    max = get_np_l(list);
    while(n!=0){        
        for(i = p; i <= p+19 && i < max; i++){
            printf("%d - %s\n", i+1, get_string_l(list, i));
        }
        printf("Total de Resultados: %d\n", max);
        printf("[1]-Pagina Anterior\n[2]-Próxima Pagina\n[0]-Sair\n");                
        scanf("%d", &n);
        if(n == 1 && p > 19) p-=20;
        else if(n == 2) p+=20;
    }
}

int main() {
    Clientes cClientes;
    Produtos cProdutos;
    List list = novo_l();
    Fact fact;/*

    cClientes = criar_clientes();
    cProdutos = criar_produtos();
    fact = criar_fact();

    ler_clientes(cClientes,  "Clientes.txt");
    ler_produtos(cProdutos, fact, "Produtos.txt");
    
    
    ler_vendas(fact, cClientes, cProdutos, "Vendas_1M.txt"); 
    
    //list = q2(cProdutos, list, 'A');
    list = q3(fact, list, 7, "NR1091", 0);
    
    //teste(fact, "GK1523");
    
    //ListProdutos = q2(CProdutos, 'A');
    travessia(list);
    /*
    ListClientes = cria_lclientes(CClientes);
    int x = get_n_l(ListClientes);
    printf("%d\n", x);
    travessia(ListClientes);
      
     */
    //print_clientes(ListClientes);
                   

    //print(fact);
    //print(fact);
    //print_whole_tree(CClientes->tree, "Cenas");
    
    // printf("%s\n", CClientes->lista->cod);

    // print_whole_tree(CProdutos->tree, "Cenas");
    // printf("%s\n", CProdutos->lista->cod);
    // printf("AVL Clientes: %d\nAVL Produtos: %d\n",(int) CClientes->tree->avl_count, (int) CProdutos->tree->avl_count);
    
    
    int n = 100;
    clock_t clock_start;
    double segundos;
    cClientes = criar_clientes();
    cProdutos = criar_produtos();
    fact = criar_fact();
   
    char*prods[25000];
    
    while (n != 0) {
        int z, w;
        int* x, y;
        float* qaux;
        char *colunas[5];
        char buff[20];
        char buff2[10];
        n = initMenu();
        switch (n) {
            case 1:
                cClientes = criar_clientes();
                cProdutos = criar_produtos();
                fact = criar_fact();
                z = getlinha("Ficheiro clientes (default: Clientes.txt):", buff, sizeof (buff));     
                clock_start=clock();
                if(!strcmp(buff, "\0"))
                    ler_clientes(cClientes, "Clientes.txt");
                else
                    ler_clientes(cClientes, buff);
                segundos = (double)(clock()- clock_start)/CLOCKS_PER_SEC;
                printf("Tempo: %.2f\n", segundos);
                
                z = getlinha("Ficheiro produtos (default: Produtos.txt):", buff, sizeof (buff));
                
                clock_start=clock();
                if(!strcmp(buff, "\0"))
                    ler_produtos(cProdutos, fact, "Produtos.txt");
                else
                    ler_produtos(cProdutos, fact, buff);
                segundos = (double)(clock()- clock_start)/CLOCKS_PER_SEC;
                printf("Tempo: %.2f\n", segundos);
                
                z = getlinha("Ficheiro Vendas (default: Vendas_1M.txt):", buff, sizeof (buff));
                clock_start=clock();
                if(!strcmp(buff, "\0"))
                    ler_vendas(fact, cClientes, cProdutos, "Vendas_1M.txt");
                else
                    ler_vendas(fact, cClientes, cProdutos, buff);
                segundos = (double)(clock()- clock_start)/CLOCKS_PER_SEC;
                printf("Tempo: %.2f\n", segundos);
                
                break;
                }
    }    
  
    return (EXIT_SUCCESS);

    //printf("END\n");
    return 0;
}