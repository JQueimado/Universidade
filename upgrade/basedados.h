#include <stdio.h>
FILE *openFile(char *filename);

void write(FILE *file,struct aeroportos *aeroporto,int pos);
void read(FILE *file,struct aeroportos *aeroporto,int pos);
int loadDb(FILE *file, struct hashtable *hash);

aeroportos* get_aeroporto(hashtable *hash, FILE *disk, char *code);
void aeroporto_to(hashtable *hash, FILE *disk, char *code, aeroportos** ret );
void write_aero(hashtable* hash, FILE* disk, aeroportos* add);