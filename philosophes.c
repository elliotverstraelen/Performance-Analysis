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
void relache_baguettes(int id);

typedef struct philosophe{
    int is_pair;
    pthread_mutex_t *right;
    pthread_mutex_t left;
} philosophe_t;

void *philosophe (void* arg)
{
    philosophe_t *id = (philosophe_t *) arg;
    printf("\n le philosophe %d pense", *id);
    for(int i=0; i<100000; i++){
        prend_baguettes(*id);
        mange(*id);
        relache_baguettes(*id);
    }
    

}
void prend_baguettes(philosophe_t *id){
    //solution assymétrique pour éviter le deadlock
    if(id->is_pair){ //si le philosophe est pair
        pthread_mutex_lock(id->left); //prend sa baguette gauche
        pthread_mutex_lock(&id->right); //prend sa baguette droite
    }
    else{ //si le philosohe est impair
        pthread_mutex_lock(&id->right); //prend sa baguette droite
        pthread_mutex_lock(id->left); //prend sa baguette gauche
    }

}

void relache_baguettes(philosophe_t *id)
{
    pthread_mutex_unlock(id->left); //relache la baguette de gauche
    pthread_mutex_unlock(&p->right); // relache la baguette de droite
}

void mange()
{
    return;
}

void error(int err, char *msg)
{
    pfrintf(stderr, "%s a retourné %d message d'erreur: %s\n", msg, err, strerror(errno));
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int nb_philosophes;
    if(argc < 3){
        // autre poss. : lance le programme avec des valeurs par defaut
        printf("Arguments inssufisants. Veuillez préciser un nombre de readers et writers.\n ./reader_writer -r <readers> -w <writers>");
    }
    else if((argv[1]!="-p") || !(argv[2].isdigit()) || (argv[1]!="--philosophes")){
        printf("Erreur dans les arguments. Veuillez préciser un nombre de readers et writers.\n ./reader_writer -r <readers> -w <writers>");
    }
    else{
        nb_philosophes = atoi(argv[2]);
        if(nb_philosophes < 1) return EXIT_FAILURE;
        if(philosophe == 1) return EXIT_SUCCES;
        printf("Starting program with %d philosophers...", nb_philosophes);
    }

    
    philosophes_t phil[nb_philosophes];
    pthread_t threads[nb_philosophes];

    //initiation des identifiants et des sémaphores des baguettes
    for(int i=0; i<nb_philosophes; i++){
        phil[i].is_pair = i%2==0;
        pthread_mutex_init(&phil[i].right, NULL);
        phil[(i+1) % nb_philosophes].left = &phil[i].right; //valeur initié à 1 car exclusion mutuelle (comme mutex)
    }

    for(int i=0; i<nb_philosophes; i++){
        pthread_create(&threads[i], NULL, philosophe, (void *)&phil[i]); //init. des thread avec fonction philosophe et argument id
    }

    for(int i=0; i<nb_philosophes; i++){
        pthread_join(threads[i], NULL);
    }
    for(int i=0; i<nb_philosophes; i++){
        pthread_mutexattr_destroy(&phil[i].right);
    }
    exit(EXIT_SUCCESS);
}
