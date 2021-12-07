all: philosophes producteurs-consommateurs reader-writer

philosophes: philosophes.c
<<<<<<< HEAD
    gcc -Wall -ansi -pedantic -o philosophes Part1/philosophes.c

producteurs-consommateurs: producteurs-consommateurs.c
    gcc -Wall -ansi -pedantic -o prod_consmateurs Part1/producteurs-consommateurs.c

reader-writer: reader-writer.c
    gcc -Wall -ansi -pedantic -o reader-writer Part1/reader-writer.c

clean:
    rm -f prog *.o
=======
	gcc -Wall -ansi -pedantic -o philosophes philosophes.c

producteurs-consommateurs: producteurs-consommateurs.c
	gcc -Wall -ansi -pedantic -o producteurs-consommateurs producteurs-consommateurs.c

reader-writer: reader-writer.c
	gcc -Wall -ansi -pedantic -o reader-writer reader-writer.c

clean: 
	rm -f reader-writer producteurs-consommateurs philosophes
>>>>>>> b9005f1289b03511df537181009c55c6764b5922
