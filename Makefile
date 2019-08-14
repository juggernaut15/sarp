sarp : main.o
	gcc -o sarp main.o

main.o : sarp_header.h sarp.h main.c
	gcc -c -o main.o main.c

clean :
	rm -rf main.o
