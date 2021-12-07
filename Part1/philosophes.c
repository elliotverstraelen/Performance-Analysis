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
    int i;
    for(i=0; i<100000; i++){
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
    if(argc != 2)
    {
        printf("Nobre d'arguments incorrecte. Veuillez préciser un nombre de philosophes.\n ./philosophes <quantité>");
        return EXIT_FAILURE;
    }
    int arg_philo;
    arg_philo = sscanf(argv[1], "%d", &nb_philosophes);
    if(arg_philo != 1)
    {
        printf("Erreur dans les arguments. %s n'est pas un nombre de producteur valide", argv[1]);
    }
    printf("le programme démarre avec %d philosophes\n", nb_philosophes);
    
    philosophe_t phil[nb_philosophes];
    pthread_t threads[nb_philosophes];

    //initiation des identifiants et des sémaphores des baguettes
    for(int i=0; i<nb_philosophes; i++){
        phil[i].is_pair = i%2==0;
        if(pthread_mutex_init(&phil[i].right, NULL) != 0)
        {
            printf("Erreur d'initiation du mutex");
        }
        phil[(i+1) % nb_philosophes].left = &phil[i].right; //valeur initié à 1 car exclusion mutuelle (comme mutex)
    }
    for(int i=0; i<nb_philosophes; i++){
        if(pthread_create(&threads[i], NULL, philosophe, (void *)&phil[i]) != 0)
        {
            printf("Erreur d'initiation du du thread");
        }
    }
    for(int i=0; i<nb_philosophes; i++){
        if(pthread_join(threads[i], NULL) != 0)
        {
            printf("Erreur de pthread_join()");
        }
    }
    for(int i=0; i<nb_philosophes; i++){
        if(pthread_mutex_destroy(&phil[i].right) != 0)
        {
            printf("Erreur de mutex_destroy()");
        }
    }
    exit(EXIT_SUCCESS);
}
