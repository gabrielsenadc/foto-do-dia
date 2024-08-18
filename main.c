#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date.h"
#include "hash.h"

int main(){
    Hash * hash = criaHash(13);

    char name[100];
    Date * date = createDate(1, 8, 2023);
    printDate(date);
    while(scanf("%[^\n]%*c", name) == 1){
        if(!strcmp(name, "next")){
            incDate(date);
            printDate(date);
        } 
        else if(!strcmp(name, "exit")) break;
        else insereHash(hash, name, date);
    } 

    FILE * output = fopen("resumo.txt", "w");

    printFileDate(date, output);

    fprintf(output, "\n");
    imprimeHash(hash, output);

    liberaHash(hash);
    freeDate(date);
    fclose(output);
    
    return 0;
}