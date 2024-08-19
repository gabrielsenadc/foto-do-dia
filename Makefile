run:
	clear
	gcc -o teste hash.c date.c main.c
	valgrind ./teste

analisa:
	gcc -o teste hash.c date.c analisa.c
	valgrind ./teste