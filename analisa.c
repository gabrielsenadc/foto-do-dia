#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date.h"
#include "hash.h"

int main(){
    Hash * hash = criaHash(13);
    char name[100];

    FILE * input = fopen("save/resumo.txt", "r");
    int day, month, year;
    if(input != NULL){
        fscanf(input, "%d/%d/%d%*c%*c", &day, &month, &year);

        int qtd = 0;
        while(fscanf(input, "%[^-]- %d%*c", name, &qtd) == 2){
            name[strlen(name) - 1] = '\0';
            
            for(int i = 0; i < qtd; i++){
                fscanf(input, "%d/%d/%d%*c", &day, &month, &year);
                Date * aux = createDate(day, month, year);
                insereInicioHash(hash, name, aux);
                free(aux);
            }
            fscanf(input, "%*c");
        }

        fclose(input);
    }

    
    scanf("%d/%d/%d", &day, &month, &year);
    Date * start = createDate(day, month, year);

    scanf("%d/%d/%d", &day, &month, &year);
    Date * end = createDate(day, month, year);

    Hash * new = filtraHash(hash, start, end);


    FILE * output = fopen("ranking.txt", "w");
    FILE * saida = fopen("analise.txt", "w");

    imprimeRank(new, output);
    imprimeHash(new, saida);
    
    freeDate(start);
    freeDate(end);
    liberaHash(new);
    liberaHash(hash);
    fclose(output);
    fclose(saida);
    
    return 0;
}