#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#define BufferSize 8
#define MaxItems 1024

//index de l'item qui sort du buffer
int in = 0;  
// index de l'item qui rentre dans le buffer
int out = 0; 

sem_t empty;
sem_t full;
int buffer[BufferSize];
pthread_mutex_t mutex;

void *producer(void *p_no);
void *consumer(void *c_no);
int process(int item);

/***
 *  simulation de traitement de ressource CPU entre chaque conso. et product.
**/
int process(int item){
    while(rand() > RAND_MAX/10000);
    return item;
}




void *producer(void *p_no)
{
    int item;
    for(int i = 0; i < MaxItems; i++)
    {
        item = process(item);
        sem_wait(&empty); //attente d'une place libre
        pthread_mutex_lock(&mutex);
        buffer[in] = item; //place l'item dans le buffer à l'index 'in'
        printf("Producteur %p a inseré l'item %d à l'emplacement %d\n", (int *)p_no, buffer[in], in);
        in = (in+1) % BufferSize; //Modulo pour répartition uniforme des valeurs, comme en hashing
        pthread_mutex_unlock(&mutex); //fin de la section critique
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *c_no)
{
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out]; //get the item to consume from the buffer
        printf("Consommateur %d a retiré l'item %d de lemplacement %d\n", *((int *)c_no), item, out);
        item = process(item); // on aurait pu faire une fonction void enfaite
        out = (out+1)%BufferSize; //Modulo pour répartition uniforme des valeurs, comme en hashing
        pthread_mutex_unlock(&mutex); //fin de la section critique
        sem_post(&empty);
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    int pro_n;
    int con_n;
    if(argc < 5){
        // autre poss. : lance le programme avec des valeurs par defaut
        printf("Arguments inssufisants. Veuillez préciser un nombre de producteurs et un nombre de consommateurs.\n ./prod_cons -p <producteurs> -c <consommateurs>");
    }
    else if(!(strncmp( argv[1], "-p", strlen( argv[1] )) == 0) || !isdigit(argv[2]) || !(strncmp( argv[3], "-c", strlen( argv[3] )) == 0) || !isdigit(argv[4])){
        printf("Erreur dans les arguments. Veuillez préciser un nombre de producteurs et un nombre de consommateurs.\n ./prod_cons -p <producteurs> -c <consommateurs>");
    }
    else{
        pro_n = atoi(argv[2]) ;
        con_n = atoi(argv[4]);

        printf("Starting program with %d producers and %d consumers...", pro_n, con_n);
    }

    pthread_t pro[pro_n], con[con_n];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BufferSize); //buffer vide
    sem_init(&full, 0, 0); //buffer vide

    for(int i = 0; i < pro_n; i++){
        void *i_ptr = &i;
        pthread_create(&pro[i], NULL, (void *)producer, i_ptr); //creation des threads produteurs [Problème de pointeur]
    }
    for(int i = 0; i < con_n; i++){
        void *i_ptr = &i;
        pthread_create(&con[i], NULL, (void *)consumer, i_ptr); //creation des threads consommateurs
    }

    //Ajouts des join statements
    for(int i=0; i < pro_n; i++){
        pthread_join(pro[i], NULL);
    }
    for(int i=0; i < con_n; i++){
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex); //release the mutex
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}