#include <stdio.h>
#include <stdlib.h>
#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2

int getlinha(char *prmpt, char *buff, size_t sz) {
    int ch, extra;


    if (prmpt != NULL) {
        printf("%s", prmpt);
        fflush(stdout);
    }
    if (fgets(buff, sz, stdin) == NULL)
        return NO_INPUT;


    if (buff[strlen(buff) - 1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }


    buff[strlen(buff) - 1] = '\0';
    return OK;
}

int initMenu() {
    int x;
    char buff[100];
    printf("##################################################################################################################################\n");
    printf("##                                                      GEREVENDAS                                                              ##\n");         
    printf("##################################################################################################################################\n");
    printf("##      [1]  - Ler os ficheiros                                                                                                 ##\n");
    printf("##      [2]  - Determinar a lista e o total de produtos cujo código se inicia por uma dada letra                                ##\n");
    printf("##      [3]  - Determinar e apresentar o número total de vendas e o total facturado com esse produto em tal mês                 ##\n");
    printf("##      [4]  - Determinar a lista ordenada dos códigos dos produtos que ninguém comprou                                         ##\n");
    printf("##      [5]  - Criar uma tabela com o número total de produtos comprados mês a mês                                              ##\n");
    printf("##      [6]  - Determinar o total de vendas registadas e o total facturado num intervalo de meses                               ##\n");
    printf("##      [7]  - Determinar a lista ordenada de códigos de clientes que realizaram compras em todas as filiais                    ##\n");
    printf("##      [8]  - Determinar os códigos dos clientes que compraram um determinado produto                                          ##\n");
    printf("##      [9]  - Determinar a lista de códigos de produtos que um cliente mais comprou por quantidade e não por facturação        ##\n");
    printf("##      [10] - Criar uma lista dos N produtos mais vendidos em todo o ano                                                       ##\n");
    printf("##      [11] - Determinar quais os códigos dos 3 produtos em que um cliente mais gastou dinheiro durante o ano                  ##\n");
    printf("##      [12] - Número de clientes registados que não realizaram compras bem como o número de produtos que ninguém comprou       ##\n");
    printf("##################################################################################################################################\n");
    x = getlinha("Input:", buff, sizeof (buff));
    return atoi(buff);

}