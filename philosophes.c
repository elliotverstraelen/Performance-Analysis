#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include<semaphore.h>
#include <string.h>



void * philosophe(void *);
void mange(int);
void error(int, char *);
void prend_baguettes(int id);
void relache_baguettes(int id)

int main(int argc, char *argv[])
{
    int philosophes = argv[argc-1];
    sem_t baguette[philosophes];
    int i;
    int id[philosophes];
    int err;
    pthread_t phil[philosophes];

    //initiation des identifiants et des sémaphores des baguettes
    for(i=0; i<philosophes; i++){
        id[i] = i;
        sem_init(&baguette[i], 0, 1); //valeur initié à 1 car exclusion mutuelle (comme mutex)
    }

    for(i=0; i<philosophes; i++){
        pthread_create(&phil[i], NULL, philosophe, (void *)&id[i]); //init. des thread avec fonctione philosophe et argument id
    }

    for(i=0; i<philosophes; i++){
        pthread_join(phil[i], NULL);
    }
}
void * philosophe (void* arg)
{
    int *id=(int *) arg;
    printf("\n le philosophe %d pense", id);

    for(int i=0; i<100000; i++){
        prend_baguettes(*id);
        mange(*id);
        relache_baguettes(*id);
    }
    

}
void prend_baguettes(int id){
    //solution assymétrique pour éviter le deadlock
    if(*id % 2 == 0){ //si le philosophe est pair
        sem_wait(&baguette[*id]); //prend sa baguette gauche
        printf("\nle philosophe %d a prit la baguette %d", *id, *id);
        sem_wait(&baguette[(*id+1)%philosophes]); //prend sa baguette droite
        printf("\nle philosophe %d a prit la baguette %d", *id, *id);
    }
    else{ //si le philosohe est impair
        sem_wait(&baguette[(*id+1)%philosophes]); //prend sa baguette droite
        printf("\nle philosophe %d a prit la baguette %d", *id, *id);
        sem_wait(&baguette[*id]); //prend sa baguette gauche
        printf("\nle philosophe %d a prit la baguette %d", *id, *id);
    }

}
void relache_baguettes(int id){
    printf("\nle philosophe %d a fini de manger", *id);
    sem_post(&baguette[(*id+1)%philosophes]); //relache la baguette de droite
    sem_post(&baguette[*id]); // relache la baguette de gauche
}

void mange(int id) {
    printf("Philosophe [%d] mange\n", id);
}
void error(int err, char *msg) {
    pfrintf(stderr, "%s a retourné %d message d'erreur: %s\n", msg, err, strerror(errno));
    exit(EXIT_FAILURE);
}

