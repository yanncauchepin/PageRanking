all : main.o liste_ref.o sommaire_site.o hachage_simple.o lecture_tsv.o
	gcc -o main *.o -Wall

liste_ref.o : liste_ref.h liste_ref.c
	gcc -c liste_ref.h liste_ref.c -Wall

sommaire_site.o : sommaire_site.h sommaire_site.c
	gcc -c sommaire_site.h sommaire_site.c -Wall

hachage_simple.o : hachage_simple.h hachage_simple.c
	gcc -c hachage_simple.h hachage_simple.c -Wall

lecture_tsv.o : lecture_tsv.h lecture_tsv.c
	gcc -c lecture_tsv.h lecture_tsv.c -Wall
	
	
main.o : liste_ref.h sommaire_site.h hachage_simple.h lecture_tsv.h main.c
	gcc -c liste_ref.h sommaire_site.h hachage_simple.h lecture_tsv.h main.c -Wall

clean : 
	rm *.o main *.gch
