all: philosophes producteurs-consommateurs reader-writer

philosophes: philosophes.c
    gcc -Wall -ansi -pedantic -o philosophes Part1/philosophes.c

producteurs-consommateurs: producteurs-consommateurs.c
    gcc -Wall -ansi -pedantic -o prod_consmateurs Part1/producteurs-consommateurs.c

reader-writer: reader-writer.c
    gcc -Wall -ansi -pedantic -o reader-writer Part1/reader-writer.c

clean:
    rm -f prog *.o
