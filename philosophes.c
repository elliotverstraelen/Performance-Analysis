#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

typedef struct philosophe{
    int is_pair;
    pthread_mutex_t *left;
    pthread_mutex_t right;
} philosophe_t;

int main(int argc, char *argv[]);
void * philosophe(void * arg);
void mange();
void prend_baguettes(philosophe_t *id);
void relache_baguettes(philosophe_t *id);


void *philosophe (void* arg)
{
    philosophe_t *id = (philosophe_t *) arg;
    for(int i=0; i<100000; i++){
        prend_baguettes(id);
        mange(id);
        relache_baguettes(id);
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
    pthread_mutex_unlock(&id->right); // relache la baguette de droite
}

void mange()
{
    return;
}

int main(int argc, char *argv[])
{
    int nb_philosophes;
    if(argc < 3){
        // autre poss. : lance le programme avec des valeurs par defaut
        printf("Arguments inssufisants. Veuillez préciser un nombre de readers et writers.\n ./reader_writer -r <readers> -w <writers>");
    }
    else if((argv[1]!="-p") || !isdigit(argv[2]) || (argv[1]!="--philosophes")){
        printf("Erreur dans les arguments. Veuillez préciser un nombre de readers et writers.\n ./reader_writer -r <readers> -w <writers>");
    }
    else{
        nb_philosophes = atoi(argv[2]);
        if(nb_philosophes < 1) return EXIT_FAILURE;
        if(nb_philosophes == 1) return EXIT_SUCCESS;
        printf("Starting program with %d philosophers...", nb_philosophes);
    }

    
    philosophe_t phil[nb_philosophes];
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
        pthread_mutex_destroy(&phil[i].right);
    }
    exit(EXIT_SUCCESS);
}
