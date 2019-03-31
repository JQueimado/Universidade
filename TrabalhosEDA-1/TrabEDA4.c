#include <stdio.h>
#include <stdlib.h>

#define ERROR NULL
#define TopLim 500000
#define BotLim 0
#define Val_TopLim 99999.99
#define Val_BotLim 0.01

//struct contribuinte
struct contribuinte {
    long nif;
    struct contribuinte *conj;
    float g, s, e, a;
};

struct contribuinte *contribuinte_new(){
    struct contribuinte *con =  malloc(sizeof(struct contribuinte));
    con->nif =0;
    con->conj = NULL;
    con->g = 0;
    con->s = 0;
    con->e = 0;
    con->a = 0;
    return con;
}

//functions

struct contribuinte *find(long f, struct contribuinte *arr[], int size){
    
    int frt = 0;
    int lst = size-1;
    
    while(frt <= lst){
        
        if(arr[frt]->nif == f)
            return arr[frt];
        frt++;
        
        if(arr[lst]->nif == f)
            return arr[lst];
        lst--;
    }
    return ERROR;
}

//main
int main(void){

    //nifs input
    int n = 0;
    scanf("%d", &n);
    
    //limites de n    
    if (n<BotLim || n>TopLim)
        return 0;
    
    struct contribuinte *nfs[n];
    
    for(int c = 0; c < n; c++){
        nfs[c] = contribuinte_new();
        scanf("%9ld", &nfs[c]->nif);
    }

    //casais input
    int n_cas = 0;
    scanf("%d",&n_cas);
    
    //limites de casais
    if(n_cas<BotLim || n_cas>n)
        return 0;
    
    while(n_cas > 0){
        long fnif;
        long snif;
        scanf("%9ld %9ld", &fnif, &snif);
    
        struct contribuinte *conj1 = find(fnif, nfs, n);
        struct contribuinte *conj2 = find(snif, nfs, n);
        conj1->conj = conj2;
        conj2->conj = conj1;
        
        n_cas--;
    }
    
    //loop
    char ch = 0;
    long nf = 0;
    float val =0.0;

    while(1){
        
        if (scanf(" %c", &ch) == EOF)
            return 0;
        
        //nf
        if (scanf("%ld", &nf) == EOF)
            return 0;        
        
        struct contribuinte *cont = find(nf, nfs, n);

        if (cont == ERROR){
             printf("contribuinte sem informacao: %09ld\n", nf);
             continue;
         }          
        
        struct contribuinte *con = cont->conj;

        //obter informação
        if (ch == '?'){
        
            //tipo de submição
            char status =0;
            if(con != NULL)
                status = 'C';
            else
                status = 'I';
        
            printf("%09ld [%c] geral%9.2f, saude%9.2f, educ.%9.2f, alim.%9.2f\n", nf, status, cont->g, cont->s, cont->e, cont->a);
            
            continue;
        }
        
        //valor
        if (scanf("%f", &val) == EOF)
            return 0;
        
        //limites de val
        if (val < Val_BotLim || val>Val_TopLim)
            return 0;
            
        //adicionar informação
        //geral
        if(ch=='g'){
            cont->g += val;

            if(con != NULL)
                con->g += val;
        }
        
        //saude
        if(ch=='s'){
            cont->s += val;

            if(con != NULL)
                con->s += val;
        }
        
        //educação
        if(ch=='e'){
            cont->e += val;

            if(con != NULL)
                con->e += val;
        }
        
        //alimentação
        if(ch=='a'){
            cont->a += val;
            cont->g += val;
            if(con != NULL){
                con->a += val;
                con->g += val;
            }
        }

    }
    
    return 0;
}





