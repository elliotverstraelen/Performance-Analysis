all: philosophes producteurs-consommateurs reader-writer

philosophes: Part1/philosophes.c
	gcc Part1/philosophes.c -lpthread -o philosophes 

producteurs-consommateurs: Part1/producteurs-consommateurs.c
	gcc Part1/producteurs-consommateurs.c  -o pro_con -lpthread -ansi -std=c99

reader-writer: Part1/reader_writer.c
	gcc Part1/reader_writer.c -o rw -lpthread -ansi -std=c99

clean:
	rm -f prog *.o
