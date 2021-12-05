all: philosophes producteurs-consommateurs reader-writer

philosophes: philosophes.c
    gcc -Wall -ansi -pedantic -o philosophes philosophes.c

producteurs-consommateurs: producteurs-consommateurs.c
    gcc -Wall -ansi -pedantic -o producteurs-consommateurs producteurs-consommateurs.c

reader-writer: reader-writer.c
    gcc -Wall -ansi -pedantic -o reader-writer reader-writer.c


