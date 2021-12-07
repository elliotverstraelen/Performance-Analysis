#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>
#include <stdlib.h>
#include <ctype.h>

pthread_rwlock_t lock_rw = PTHREAD_RWLOCK_INITIALIZER;
int read_ops = 2560;
int write_ops = 640;
int nb_writer, nb_reader;
int readcount, writecount;

pthread_mutex_t w_mutex, r_mutex;
sem_t w_db, r_db; //initialisation des semaphores pour excl. 'accès à la db

//Fonction qui "simule" le calcule effectué par le thread reader ou writer
void process(void){
    while(rand() > RAND_MAX/10000){
        continue;
    }
    return;
}

void *reader(void *rd_n){
    int runner = 1;
    for(int i=0; i<read_ops; i++){
        sem_wait(&r_db);
        pthread_mutex_lock(&r_mutex);
        readcount++;
        if(readcount==1)
        {
            //arrivée du premier writer
            sem_wait(&w_db);
        }
        pthread_mutex_unlock(&r_mutex);
        sem_post(&r_db);

        process();

        pthread_mutex_lock(&r_mutex);
        readcount--;
        if(readcount == 0)
        {
            sem_post(&w_db);
        }
        pthread_mutex_unlock(&r_mutex);
    }
    return NULL;
}

void *writer(void *wr_n){
    int runner = 1;
    for(int i=0; i<write_ops; i++){
        pthread_mutex_lock(&w_mutex);
        //section critique
        writecount++;
        if(writecount==1){
            //arrivée du premier reader
            sem_wait(&r_db);
        }
        pthread_mutex_unlock(&w_mutex);

        sem_wait(&w_db);
        process();
        sem_post(&w_db);

        pthread_mutex_lock(&w_mutex);
        
        //section critique
        writecount--;
        if(writecount==0){
            //départ du dernier reader
            sem_post(&r_db);
        }
        pthread_mutex_unlock(&w_mutex);
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    int rd_n, wr_n;

    if(argc != 3)
    {
        printf("Arguments inssufisants. Veuillez préciser un nombre de readers et writers.\n ./reader_writer -r <readers> -w <writers>");
        return EXIT_FAILURE;
    }
    int arg_read = sscanf(argv[1], "%d", &rd_n);
    int arg_write = sscanf(argv[2], "%d", &wr_n);
    if(arg_read != 1)
    {
        printf("Erreur dans les arguments. %s n'est pas un nombre de reader valide", argv[1]);
    }
    if(arg_write !=1)
    {
        printf("Erreur dans les arguments. %s n'est pas un nombre de writer valide.", argv[2]);
    }

    printf("le programme démarre avec %d readers et %d writers\n", rd_n, wr_n);

    //Initialisation des mutex
    if(pthread_mutex_init(&r_mutex, NULL) !=0){
        printf("Error creating reading mutex");
    }
    if(pthread_mutex_init(&w_mutex, NULL) !=0){
        printf("Error creating writer mutex");
    }
    //Initialisation des semaphores
    if(sem_init(&r_db, 0, 1) !=0){
        printf("Error creating reading semaphore");
    }
    if(sem_init(&w_db, 0, 1) !=0){
        printf("Error creating writing semaphore");
    }

    void *vp;
    //creation des threads readers et writers
    pthread_t readers[rd_n], writers[wr_n];
    for(int i=0; i<rd_n; i++)
    {
        if((pthread_create(&readers[i], NULL, reader, NULL) != 0))
        {
            perror("erreur de creation du thread reader");
            exit(-1);
        }
    }
    for(int i=0; i<wr_n; i++)
    {
        if((pthread_create(&writers[i], NULL, writer, NULL) != 0))
        {
            perror("erreur de creation du thread writer");
            exit(-1);
        }
    }
    //attente de terminaison des threads
    for(int i=0; i<rd_n; i++)
    {
        if(pthread_join(readers[i], NULL) !=0){
            perror("erreur pthread_join readers");
            exit(-1);
        }
    }
    for(int i=0; i<wr_n; i++)
    {
        if(pthread_join(writers[i], NULL) !=0)
        {
            perror("erreur pthread_join writers");
            exit(-1);
        }
    }
    pthread_mutex_destroy(&w_mutex);
    pthread_mutex_destroy(&r_mutex);
    sem_destroy(&w_db);
    sem_destroy(&r_db);

    return 0;
}

