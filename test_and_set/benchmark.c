#include "spin.h"

spin_t spin; //Ajout du locker
int workload = 6400;
int n_threads;

int main(int argc, char *argv[])
{
    if(argc != 3){
        // autre poss. : lance le programme avec des valeurs par defaut
        printf("Arguments inssufisant");
        exit(EXIT_FAILURE);
    }
    if(argv[1] != "-t" || argv[1]!= "--threads" || !sidigit(argv[2]))
    {
        printf("Arguments inssufisant");
        exit(EXIT_FAILURE);
    }
    n_threads = argv[2];
    if(n_threads < 1) return EXIT_FAILURE;
    
    //Création des threads -> à implémenter

}