#include <stdio.h>

FILE *openFile(char *filename);
void write(FILE *file,struct aeroportos *aeroporto,int pos);
void read(FILE *file,struct aeroportos *aeroporto,int pos);
void loadDb(FILE *file, struct hashtable *hash);