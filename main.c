#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date.h"
#include "hash.h"

int main(){
    Hash * hash = criaHash(13);
    Date * date = createDate(1, 8, 2023);
    char name[100];

    FILE * input = fopen("save/resumo.txt", "r");
    if(input != NULL){
        int day, month, year;
        fscanf(input, "%d/%d/%d%*c%*c", &day, &month, &year);
        setDate(date, day, month, year);
        incDate(date);

        int qtd = 0;
        while(fscanf(input, "%[^-]- %d%*c", name, &qtd) == 2){
            name[strlen(name) - 1] = '\0';
            printf("%s %d\n", name, qtd);
            
            for(int i = 0; i < qtd; i++){
                fscanf(input, "%d/%d/%d%*c", &day, &month, &year);
                Date * aux = createDate(day, month, year);
                insereHash(hash, name, aux);
                free(aux);
            }
            fscanf(input, "%*c");
        }

        fclose(input);
    }


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