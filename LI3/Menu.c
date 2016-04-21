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
    printf("#########################\n");
    printf("GEREVENDAS\n");
    printf("#########################\n\n");

    printf("[1]  - Ler ficheiros\n");
    printf("\n#########################\n");
    x = getlinha("#:", buff, sizeof (buff));
    return atoi(buff);

}