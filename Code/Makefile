all : main.o list_ref.o simple_hashing.o read_tsv.o utils.o
	gcc -g -o ../pageranking *.o -Wall -lm

utils.o : utils.h utils.c
	gcc -c utils.h utils.c -Wall

list_ref.o : list_ref.h list_ref.c
	gcc -c list_ref.h list_ref.c -Wall

simple_hashing.o : simple_hashing.h simple_hashing.c
	gcc -c simple_hashing.h simple_hashing.c -Wall

read_tsv.o : read_tsv.h read_tsv.c
	gcc -c read_tsv.h read_tsv.c -Wall

main.o : list_ref.h simple_hashing.h read_tsv.h utils.h main.c
	gcc -c list_ref.h simple_hashing.h read_tsv.h utils.h main.c -Wall

clean :
	rm *.o *.gch ../pageranking
