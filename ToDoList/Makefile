all: list_prog

list_prog: todolist.o comandos.o
	gcc -o list_prog todolist.o comandos.o

todolist.o: todolist.c todolist.h
	gcc -o todolist.o todolist.c -c -W -Wall -std=gnu99 -pedantic

comandos.o: comandos.c todolist.h
	gcc -o comandos.o comandos.c -c -W -Wall -std=gnu99 -pedantic

clean:
	rm -rf *.o *~ list_prog