#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>
#include <stdlib.h>

pthread_rwlock_t lock_rw = PTHREAD_RWLOCK_INITIALIZER;

int main(int argc, char* argv[])
{
    int rd_n, wr_n;
    if(argc < 5){
        // autre poss. : lance le programme avec des valeurs par defaut
        printf("Arguments inssufisants. Veuillez préciser un nombre de readers et writers.\n ./reader_writer -r <readers> -w <writers>");
    }
    else if((argv[1]!="-r") || !(argv[2].isdigit()) || (argv[3]!="-w") || !(argv[4].isdigit()) ){
        printf("Erreur dans les arguments. Veuillez préciser un nombre de readers et writers.\n ./reader_writer -r <readers> -w <writers>");
    }
    else{
        rd_n = argv[2];
        wr_n = argv[4];
        printf("Starting program with %d readers and %d writers...", rd_n, wr_n);
    }
    void *vp;
    //creation des threads readers et writers
    pthread_t readers[rd_n], writers[wr_n];
    for(int i=0; i<rd_n; i++){
        if((pthread_create(*readers[i], NULL, *reader, &lock_rw) != 0){ //probleme de pointuer ?
            perror("erreur de creation du thread reader");
            exit(-1);
        }
    }
    for(int i=0; i<wr_n; i++){
        if((pthread_create(*writers[i], NULL, *writer, &lock_rw) != 0){ //probleme de pointuer ?
            perror("erreur de creation du thread writer");
            exit(-1);
        }
    //attente de terminaison des threads
    for(int i=0; i<rd_n; i++){
        if(pthread_join(*readers[i], &vp) !=0){
            perror("erreur pthread_join readers");
            exit(-1);
        }
    }
    for(int i=0; i<wr_n; i++){
        if(pthread_join(*writers[i], &vp) !=0){
            perror("erreur pthread_join writers");
            exit(-1);
        }
    }
    return 0
}
void *reader(void *rd_n){
    pthread_rwlock_t lock;
    pthread_rwlock_init(&lock, NULL);
    //TODO
}
void *writer(void *wr_n){
    //TODO
}
int process(int item){
    while(rand() > RAND_MAX/10000){
        continue;
    }
    return item;
}
