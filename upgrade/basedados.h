#include <stdio.h>
#include <stdlib.h>

#include "aeroporto.h"
#include "hashtable.h"

FILE *openFile(char *filename);

void write(FILE *file,struct aeroportos *aeroporto,int pos);

void read(FILE *file,struct aeroportos *aeroporto,int pos);

int loadDb(FILE *file, struct hashtable *hash);

void aeroporto_to(hashtable *hash, FILE *disk, char *code, aeroportos** ret );