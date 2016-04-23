#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "CatC.h"
#include "CatP.h"
#include "Fact.h"
#include "Filial.h"
#include "List.h"

void *ler_clientes(Clientes cC, Filial fil, char *filename) {
    int X = 10, i = 0, flag = 0, lidos = 0;
    char s[10];
    char* cod;
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        while (fgets(s, X, f)) {
            cod = strtok(s, "\r\n");
            cC = insert_clientes(cC, cod);
            fil = instert_clientesFil(fil, cod);
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
            fact = insert_produtosF(fact, cod);
            cod = (char*) malloc(10);
            lidos++;
        }
    }

    printf("Produtos lidos: %d\n", lidos);
    return NULL;
}

int ler_vendas(Fact fact, Filial fil, Clientes cC, Produtos cP, char * filename) {
    int X = 100, i = 0, lidos = 0, unidades = 0, mes = 0, filial = 0; //Necessário verificar se codigo de Prod e de Cliente
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
            if (!check_produto(cP, codProd) && !check_cliente(cC, codCliente)) {
                fact = insert_vendasF(fact, codProd, valor, unidades, promo, mes, filial);
                fil = insert_vendas_Filial(fil, codProd, valor, unidades, promo, codCliente, mes, filial);
                certos++;
            } else
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

void travessia(List list, float s) {
    int st = 1, i = 0, p = 0, max,m;
    max = get_np_l(list);
    while (st != 0) {
        for (i = p; i <= p + 19 && i < max; i++) {
            printf("%s\n", get_string_l(list, i));
        }
        printf("Resultados apresentados: %d\n", i);
        printf("Total de Resultados: %d\n", max);
        printf("Tempo: %.2f\n", s);
        printf("[1]-Pagina Anterior\n[2]-Próxima Pagina\n[0]-Sair\n");
        scanf("%d", &st);
        if(st==0)
           m=initMenu();
        if (st == 1 && p > 19) p -= 20;
        else if (st == 2) p += 20;
    }
}

int main() {
    Clientes cClientes;
    Produtos cProdutos;
    List list = novo_l();
    List list2 = novo_l();
    Fact fact;
    char* prod;
    char* aux = (char*) malloc(sizeof (char*)*30);
    Filial filial;

    int n = 100;
    clock_t clock_start;
    double segundos;
    cClientes = criar_clientes();
    cProdutos = criar_produtos();
    fact = criar_fact();
    filial = criar_filial();

    while (n != 0) {

        int z, w, f, k;
        int* x, y;
        char l;
        float* qaux;
        char* cli;
        char* cprod;
        char *colunas[5];
        char buff[20];
        char buff2[10];
        char buff3[5];
        n = initMenu();
        switch (n) {
            case 1:
                cClientes = criar_clientes();
                cProdutos = criar_produtos();
                fact = criar_fact();
                z = getlinha("Ficheiro clientes (default: Clientes.txt):", buff, sizeof (buff));
                clock_start = clock();
                if (!strcmp(buff, "\0"))
                    ler_clientes(cClientes, filial, "Clientes.txt");
                else
                    ler_clientes(cClientes, filial, buff);
                segundos = (double) (clock() - clock_start) / CLOCKS_PER_SEC;
                printf("Tempo: %.2f\n", segundos);

                z = getlinha("Ficheiro produtos (default: Produtos.txt):", buff, sizeof (buff));

                clock_start = clock();
                if (!strcmp(buff, "\0"))
                    ler_produtos(cProdutos, fact, "Produtos.txt");
                else
                    ler_produtos(cProdutos, fact, buff);
                segundos = (double) (clock() - clock_start) / CLOCKS_PER_SEC;
                printf("Tempo: %.2f\n", segundos);

                z = getlinha("Ficheiro Vendas (default: Vendas_1M.txt):", buff, sizeof (buff));
                clock_start = clock();
                if (!strcmp(buff, "\0"))
                    ler_vendas(fact, filial, cClientes, cProdutos, "Vendas_1M.txt");
                else
                    ler_vendas(fact, filial, cClientes, cProdutos, buff);
                segundos = (double) (clock() - clock_start) / CLOCKS_PER_SEC;
                printf("Tempo: %.2f\n", segundos);

                break;

            case 2:
                z = getlinha("Insira a letra:\n", buff, sizeof (buff));
                clock_start = clock();
                list = q2(cProdutos, list, buff[0]);
                segundos = (double) (clock() - clock_start) / CLOCKS_PER_SEC;
               travessia(list, segundos);


                break;

            case 3:
                z = getlinha("Insira o mês:\n", buff, sizeof (buff));
                w = atoi(buff);
                z = getlinha("Insira o código de produto:\n", buff2, sizeof (buff2));
                cprod = buff2;
                printf("Qual o tipo de facturação que pretende visualizar?\n");
                z = getlinha("[0]- Facturação Global\n[1]- Facturação Filial 1\n[2]- Facturação Filial 2\n[3]- Facturação Filial 3\n", buff, sizeof (buff));
                f = atoi(buff);
                clock_start = clock();
                if (f >= 0 && f <= 3) {
                    list = q3(fact, list, w, cprod, f);
                    segundos = (double) (clock() - clock_start) / CLOCKS_PER_SEC;
                    travessia(list, segundos);
                } else {
                    printf("Erro: O valor tem de estar entre 0 e 3\n");
                    z = getlinha("[0]- Facturação Global\n[1]- Facturação Filial 1\n[2]- Facturação Filial 2\n[3]- Facturação Filial 3\n", buff, sizeof (buff));
                    f = atoi(buff);
                    clock_start = clock();
                    list = q3(fact, list, w, cprod, f);
                    segundos = (double) (clock() - clock_start) / CLOCKS_PER_SEC;
                    travessia(list, segundos);
                }
                break;

          case 4:
                printf("Qual o tipo de facturação que pretende visualizar?\n");
                k=getlinha("[0]- Facturação Global\n[1]- Facturação Filial 1\n[2]- Facturação Filial 2\n[3]- Facturação Filial 3\n",buff, sizeof (buff));
                w = atoi(buff);
                clock_start=clock();
               list=q4(fact,list,w);
                segundos = (double) (clock() - clock_start) / CLOCKS_PER_SEC;
                    travessia(list, segundos);

            case 5:
                z = getlinha("Insira o código de cliente:\n", buff, sizeof (buff));
                cli = buff;
                clock_start = clock();
                list = q5(filial, list, cli);
                segundos = (double) (clock() - clock_start) / CLOCKS_PER_SEC;
                travessia(list, segundos);
                break;

            case 6:
                z = getlinha("Insira o primeiro mês:\n", buff, sizeof (buff));
                w = atoi(buff);
                z = getlinha("Insira o segundo mês:\n", buff2, sizeof (buff2));
                f = atoi(buff2);
                clock_start = clock();
                q6(fact, list, w, f);
                segundos = (double) (clock() - clock_start) / CLOCKS_PER_SEC;
                travessia(list, segundos);

                break;

            case 7:
                clock_start = clock();
                list = q7(filial, list);
                segundos = (double) (clock() - clock_start) / CLOCKS_PER_SEC;
                travessia(list, segundos);
                break;

            case 8:
                z = getlinha("Insira o código do produto:\n", buff, sizeof (buff));
                w = getlinha("Insira o número da Filial(1,2 ou 3):\n", buff2, sizeof (buff2));

                k = atoi(buff2);
                clock_start = clock();
                list = q8(filial, list, buff, k);
                segundos = (double) (clock() - clock_start) / CLOCKS_PER_SEC;
                travessia(list, segundos);



                break;
            case 9:
                z = getlinha("Insira o código de cliente:\n", buff, sizeof (buff));
                cli = buff;
                f = getlinha("Insira o mês:\n", buff2, sizeof (buff2));
                w = atoi(buff2);
                clock_start = clock();
                list = q9(filial, list, cli, w);
                segundos = (double) (clock() - clock_start) / CLOCKS_PER_SEC;
                travessia(list, segundos);


                break;
            case 10:

                z = getlinha("Insira o número de Produtos que pretende ver:\n", buff, sizeof (buff));
                w = atoi(buff);
                clock_start = clock();
                list = q10_fact(fact, list, w);
                list = q10_fili(filial, list, w);
                segundos = (double) (clock() - clock_start) / CLOCKS_PER_SEC;
                travessia(list, segundos);

                break;
            case 11:
                z = getlinha("Insira o código de cliente:\n", buff, sizeof (buff));
                cli = buff;
                clock_start = clock();
                list = q11(filial, list, cli);
                segundos = (double) (clock() - clock_start) / CLOCKS_PER_SEC;
                travessia(list, segundos);


                break;

            case 12:
                clock_start = clock();
                list = q12_fact(fact, list);
                list = q12_fili(fact, list);
                segundos = (double) (clock() - clock_start) / CLOCKS_PER_SEC;
                travessia(list, segundos);
                break;
        }
    }

    return (EXIT_SUCCESS);

    //printf("END\n");
    return 0;
}