#ifndef hash_h
#define hash_h

#include <stdio.h>
#include "date.h"

typedef struct hash Hash;

Hash * criaHash(int size);

void insereHash(Hash *hash, char *name, Date * date);

void insereInicioHash(Hash *hash, char *name, Date * date);

void liberaHash(Hash * hash);

void imprimeHash(Hash *hash, FILE * output);


#endif