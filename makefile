build = $(wildcard build/*.o)

.PHONY: main

uno: uno.o
	gcc $(build) -o bin/uno -lm

uno.o:
	gcc -c src/uno.c -o build/uno.o
	