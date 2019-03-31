#include <stdio.h>
#include <stdlib.h>

#define STD_Size 10000
#define STD_N_lim 99999
#define STD_O_lim 100000
#define STD_T_lim 1000000

#define STD_cord_lim 59

#define STD_lat_bot_lim -90 
#define STD_lat_top_lim 90 

#define STD_log_bot_lim -179 
#define STD_log_top_lim 180 

//class inf
struct inf{
    long inst;
    int lat[3];
    int log[3];
};

struct inf *inf_new(long i, int lat[], int log[]){
    struct inf *temp = malloc(sizeof(struct inf));
    temp->inst = i;
    
    temp->lat[0] = lat[0];
    temp->lat[1] = lat[1];
    temp->lat[2] = lat[2];
    
    temp->log[0] = log[0];
    temp->log[1] = log[1];
    temp->log[2] = log[2];
    
    return temp;
}


//class suspeito
struct suspeito {
    long n_suspeito;
    struct inf *inf_arr[STD_Size];
    int c;
};

struct suspeito *suspeito_new(long n, long i, int lat[], int log[]){
    struct suspeito *temp =  malloc(sizeof(struct suspeito));
    temp->n_suspeito = n;
    temp->inf_arr[0] = inf_new(i, lat, log);
    temp->c = 1;
    return temp;
}

void suspeito_addInst(struct suspeito *sus, long i, int lat[], int log[]){
    sus->inf_arr[sus->c] = inf_new(i, lat, log);
    sus->c += 1;
}

//class list
struct node{
    struct node *next;
    struct suspeito *elem;
};

struct list {
    struct node *header;
    int size;
};

struct list *list_new(){
    
    struct list *l = malloc(sizeof(struct list));
    
    //header
    struct node *header = malloc(sizeof(struct node));
    header->elem = NULL;
    header->next = NULL;
    
    l->header = header;
    l->size = 0;
    
    return l;
}

void list_add(struct list *l, struct suspeito *e){
    struct node *temp = malloc(sizeof(struct node));
    temp->elem = e;
    temp->next = NULL;
    
    struct node *last = l->header;
    
    while(last->next != NULL){
        last = last->next;
    }
    
    last->next = temp;
    l->size += 1;
}

struct suspeito *list_find(struct list *l, long n){
    
    if(l->size == 0)
        return NULL;
    
    struct node *cur = l->header->next;
    
    while(cur != NULL){
        
        if (cur->elem->n_suspeito == n){
            return cur->elem;
        }
        cur = cur->next;
    }
    
    return NULL;
    
}

int eval_cords(struct inf *cords1, struct inf *cords2){
    
    for (int i = 0; i<3; i++){
    
        if (cords1->lat[i] != cords2->lat[i] || cords1->log[i] != cords2->log[i])
            return 0;    
    }
    
    return 1;
}


//main
int main( void ){
    long n_suspeito = 0;
    long inst = 0;    
    int latitude[] = {0, 0, 0};
    int longitude[] = {0, 0, 0};
    
    long counter = 0;
        
    struct list *sus = list_new();
    
    long casos[2*10];
    int casos_size = 0;
    
    while(1){
        if (scanf("%05li", &n_suspeito)== EOF)
            break;
        
        if (sus->size > STD_N_lim || sus->size < 0)
            return 0;
            
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
            //puts("control");
            if (latitude[0] > STD_lat_top_lim || latitude[0] < STD_lat_bot_lim)
                return 0;
            //puts("control");
            if (longitude[0] > STD_log_top_lim || longitude[0] < STD_log_bot_lim)
                return 0;
            //puts("control");    
            if (latitude[1] > STD_cord_lim || latitude[1] < 0)
                return 0;
            //puts("control");   
            if (latitude[2] > STD_cord_lim || latitude[2] < 0)
                return 0;
            //puts("control");
            if (longitude[1] > STD_cord_lim || longitude[1] < 0)
                return 0;
            //puts("control");    
            if (longitude[2] > STD_cord_lim || longitude[2] < 0)
                return 0;
            
            if (val == EOF)
                break;
            
            struct suspeito *temp = list_find(sus,n_suspeito);

            if (temp != NULL){
                counter +=1;
                
                if (temp->c > STD_O_lim || counter > STD_T_lim || temp->c < 0 || counter < 0)
                    return 0;
                
                suspeito_addInst(temp, inst, latitude, longitude);
                
            }else{    
                
                list_add(sus, suspeito_new(n_suspeito, inst, latitude, longitude));
                
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
    
    //eval casos
    for(int c = 0; c<casos_size; c+=2){
        
        struct suspeito *sus1 = list_find(sus, casos[c]);
        struct suspeito *sus2 = list_find(sus, casos[c+1]);
        
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
        short flag = 0;
        for (int i = 0; i<sus1->c; i++){
            
            long inst = sus1->inf_arr[i]->inst;
            
            int top = sus2->c - 1;
            int bot = 0;       
            
            while (top >= bot){
                
                int mid = (top+bot)/2;
                long cur = sus2->inf_arr[mid]->inst;
                
                
                if (cur == inst){
                    
                    struct inf *inf1 = sus1->inf_arr[i];
                    struct inf *inf2 = sus2->inf_arr[mid];
                    
                    if (eval_cords(inf1, inf2) == 1){
                    
                        if (flag == 0)
                            printf("+ %05li e %05li podem ter-se encontrado em:\n",sus1->n_suspeito, sus2->n_suspeito);
                        flag = 1;
                        
                        printf("%li %d %d\' %d\" %d %d\' %d\"\n", 
                                inf2->inst, 
                                inf2->lat[0], 
                                inf2->lat[1], 
                                inf2->lat[2],
                                inf2->log[0],
                                inf2->log[1],
                                inf2->log[2]
                              ); 
                    
                    }
                
                } 
                   
                if (inst < cur){
                    top = mid - 1;
                }else{
                    bot = mid + 1;
                }
            }
            
        }
        
        if(flag == 0)
           printf("+ %05li e %05li nunca se encontraram (aparentemente)\n",sus1->n_suspeito, sus2->n_suspeito);
        
    }
    
    return 0;
}






















