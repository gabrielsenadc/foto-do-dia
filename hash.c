#include <stdlib.h>
#include <string.h>
#include "hash.h"

typedef struct person Person;

struct hash{
    Person **tab;
    int size;
};

struct person{
    Person *next;
    char *name;
    DateList * dates;
    int qtd;
};

int hashFunction(char * name, int size){
    int total = 0;
    for(int i = 0; i < strlen(name); i++) total += name[i];

    return total % size;
}

Hash * criaHash(int size){
    Hash * hash = malloc(sizeof(Hash));

    hash->tab = calloc(size, sizeof(Person*));
    hash->size = size;

    return hash;
}

void insereHash(Hash *hash, char *name, Date * date){
    int index = hashFunction(name, hash->size);

    Person *aux = hash->tab[index];

    while(aux){
        if(!strcmp(aux->name, name)) break;
        aux = aux->next;
    }

    if(aux == NULL){
        aux = malloc(sizeof(Person));

        aux->name = strdup(name);
        aux->next = hash->tab[index];
        hash->tab[index] = aux;

        aux->dates = createDateList();
        aux->qtd = 0;
    }

    Date * new = copyDate(date);
    insertDate(aux->dates, new);
    aux->qtd++;
}

void liberaPerson(Person * cell){
    if(cell == NULL) return;

    free(cell->name);
    freeDateList(cell->dates);
    liberaPerson(cell->next);

    free(cell);
}

void liberaHash(Hash * hash){
    for(int i = 0; i < hash->size; i++){
        liberaPerson(hash->tab[i]);
    }

    free(hash->tab);
    free(hash);
}

int getQtdHash(Hash * hash){
    int total = 0;
    for(int i = 0; i < hash->size; i++){
        Person * aux = hash->tab[i];
        while(aux){
            total++;
            aux = aux->next;
        }
    }

    return total;
}

int qtdPeopleHash(Hash * hash){
    int total = 0;
    for(int i = 0; i < hash->size; i++){
        Person * aux = hash->tab[i];
        while(aux){
            total += aux->qtd;
            aux = aux->next;
        }
    }

    return total;
}

int getQtdPerson(Person * person){
    if(person == NULL) return 0;
    return person->qtd;
}

Person * getMaiorFrequencia(Hash * hash){
    Person * higher = NULL;

    for(int i = 0; i < hash->size; i++){
        Person * aux = hash->tab[i];
        while(aux) {
            if(getQtdPerson(aux) > getQtdPerson(higher)) higher = aux;
            aux = aux->next;
        }
    }

    return higher;
}

int comparePeopleHash(const void * word1, const void * word2){
    Person *w1 = *(Person**) word1;
    Person *w2 = *(Person**) word2;

    if(w1->qtd != w2->qtd) return w2->qtd - w1->qtd;
    return strcmp(w1->name, w2->name); 
}

void imprimeHash(Hash *hash, FILE * output){
    int tam = getQtdHash(hash), j = 0;

    Person *vet[tam];
    for(int i = 0; i < hash->size; i++){
        Person * aux = hash->tab[i];
        while(aux){
            vet[j] = aux;
            j++;
            aux = aux->next;
        }
    }

    qsort(vet, tam, sizeof(Person*), comparePeopleHash);

    for(int i = 0; i < tam; i++){
        fprintf(output, "%s %d:\n", vet[i]->name, vet[i]->qtd);
        printFileDateList(vet[i]->dates, output);
        fprintf(output, "\n");
    }

}

