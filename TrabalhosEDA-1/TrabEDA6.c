#include <stdio.h>
#include <stdlib.h>

struct suspeito {
    long n_suspeito;
    long Instante[10];
    int c;
    struct cords *latitude[10];
    struct cords *longitude[10];
};

struct cords{
    int x;
    int y;
    int z;
};

struct cords *cords_new(int arr[]){
    struct cords *c =  malloc(sizeof(struct suspeito));
    c->x = arr[0];
    c->y = arr[1];
    c->z = arr[2];
    return c;
}

struct suspeito *suspeito_new(int n, long i, int lat[], int log[]){
    struct suspeito *s =  malloc(sizeof(struct suspeito));
    struct cords *la = cords_new(lat);
    struct cords *lo = cords_new(log);
    s->c = 1;
    s->n_suspeito   = n;
    s->Instante[0]  = i;
    s->latitude[0]  = la;
    s->longitude[0] = lo;
    return s;
}

void add_Inst(struct suspeito *sus, long i, int lat[], int log[]){
    int cur = sus->c;
    struct cords *la = cords_new(lat);
    struct cords *lo = cords_new(log);
    
    sus->Instante [cur] = i;
    sus->latitude [cur] = la;
    sus->longitude[cur] = lo;
    
    sus->c += 1;
    
}

int partition(struct suspeito *arr[], int high, int low){

    struct suspeito *pivot = arr[high];  
 
    int i = (low - 1); 

    for (int j = low; j <= high- 1; j++){
       
        if (arr[j]->n_suspeito <= pivot->n_suspeito){
            i++;
            struct suspeito *temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    struct suspeito *temp = arr[high];
    arr[i+1] = arr[high];
    arr[high] = temp;
    
    return (i + 1);
}

void quick_sort(struct suspeito *arr[], int high, int low){
    
    if(high > low){
        int part = partition( arr, high, low);
        
        quick_sort(arr, part-1, low);
        quick_sort(arr, high, part+1);
    }
    
}

int suspeito_partition(struct suspeito *sus, int high, int low){

    long pivot = sus->Instante[high];  
 
    int i = (low - 1); 

    for (int j = low; j <= high- 1; j++){
       
        if (sus->Instante[j] <= pivot){
            i++;
            
            long temp = sus->Instante[i];
            sus->Instante[i] = sus->Instante[j];
            sus->Instante[j] = temp;
            
            struct cords *temp1 = sus->latitude[i];
            sus->latitude[i] = sus->latitude[j];
            sus->latitude[j] = temp1;
            
            struct cords *temp2 = sus->longitude[i];
            sus->longitude[i] = sus->longitude[j];
            sus->longitude[j] = temp2;
            
        }
    }
    
    long temp = sus->Instante[high];
    sus->Instante[i+1] = sus->Instante[high];
    sus->Instante[high] = temp;
    
    return (i + 1);
}

void suspeito_quick_sort(struct suspeito *sus, int high, int low){
    
    if(high > low){
        int part = suspeito_partition( sus, high, low);
        
        suspeito_quick_sort(sus, part-1, low);
        suspeito_quick_sort(sus, high, part+1);
    }
    
}

struct suspeito *find(struct suspeito *arr[], int n, long cod ){
    
    int top = n-1;
    int bot = 0;
    
    while (top >= bot){
        
        int mid = (top+bot)/2;
        struct suspeito *temp = arr[mid];
        
        if (temp->n_suspeito == cod)
            return temp;
        
        if (cod < temp->n_suspeito){
            top = mid - 1;
        }else{
            bot = mid + 1;
        }
        
    }
    
    return NULL;

}

int find_inst(struct suspeito *sus, long inst){
    
    int top = sus->c-1;
    int bot = 0;
    
    while (top >= bot){
        
        int mid = (top+bot)/2;
        long temp = sus->Instante[mid];
        
        if (temp == inst)
            return mid;
                    
        if (inst < temp){
            top = mid - 1;
        }else{
            bot = mid + 1;
        }
        
    }
    
    return -1;
    
}

int eval_cords(struct cords *cords1, struct cords *cords2){
    
    if(cords1->x != cords2->x)
        return 0;
        
    if(cords1->y != cords2->y)
        return 0;
        
    if(cords1->z != cords2->z)
        return 0;
    
    return 1;
}

void eval(struct suspeito *sus1, struct suspeito *sus2){

    short flag =0;
    
    for(int i = 0; i < sus1->c; i++){
        int val  = find_inst(sus2, sus1->Instante[i]);
        
        if(val != -1){
            int val2 = eval_cords( sus1->latitude[i], sus2->latitude[val] );
            int val3 = eval_cords(sus1->longitude[i], sus2->longitude[val]);
            
            if (val2==1 && val3==1){
                
                if (flag == 0)
                    printf("+ %05li e %05li podem ter-se encontrado em:\n",sus1->n_suspeito, sus2->n_suspeito);
                flag = 1;
                
                struct cords *lat = sus2->latitude[val];
                struct cords *log = sus2->longitude[val];
                
                printf("%li %d %d\' %d\" %d %d\' %d\"\n", sus2->Instante[val], lat->x, lat->y, lat->z, log->x, log->y, log->z); 
            }
        }
        
    }
    
    if(flag == 0)
        printf("+ %05li e %05li nunca se encontraram (aparentemente)\n",sus1->n_suspeito, sus2->n_suspeito);

}

//main
int main( void ){
    long n_suspeito = 0;
    long inst = 0;    
    int latitude[] = {0, 0, 0};
    int longitude[] = {0, 0, 0};
    
    struct suspeito *sus[10];
    int sus_size = 0;
    
    long casos[2*10];
    int casos_size = 0;
    
    while(1){
        if (scanf("%05li", &n_suspeito)== EOF)
            break;

        if (n_suspeito != 0){
            
            int val = scanf(
                            " %li %d %d\' %d\" %d %d\' %d\"", 
                            &inst,
                            &latitude[0], 
                            &latitude[1], 
                            &latitude[2], 
                            &longitude[0], 
                            &longitude[1], 
                            &longitude[2] 
                           );
                     
            if (val == EOF)
                break;
                
            struct suspeito *temp = find(sus, sus_size, n_suspeito);
                
            if (temp != NULL){
                
                add_Inst(temp, inst, latitude, longitude);
                suspeito_quick_sort(temp, 0, temp->c-1);
                
            }else{
                
                sus[sus_size] = suspeito_new(n_suspeito, inst ,latitude, longitude);
                sus_size += 1;
                quick_sort(sus, sus_size-1, 0);
            
            }
        
        }else{
            long n_suspeito2 = 0;

            while(scanf("%05li %05li", &n_suspeito, &n_suspeito2) != EOF){
                casos[casos_size]   = n_suspeito;
                casos[casos_size+1] = n_suspeito2;
                casos_size += 2;
            }
            
            break;
        }
    }
    
    //pa cima ta tb bem
    
    //avaliacao de casos
    
    for(int c = 0; c<casos_size; c+=2){
        
        struct suspeito *sus1 = find(sus, sus_size, casos[c]);
        struct suspeito *sus2 = find(sus, sus_size, casos[c+1]);
        
        if (sus1 == NULL){
            printf ("+ sem dados sobre os suspeitos %05li",casos[c]);
            if (sus2 == NULL){
                printf(" e %05li", casos[c+1]);
            }
            puts("");
            continue;
        }
        
        if (sus2 == NULL){
                printf("+ sem dados sobre os suspeitos %05li\n", casos[c+1]);
                continue;
        }
        
        //eval
        eval(sus1,sus2);
    }
    return 0;
}
