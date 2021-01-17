CC=gcc
OPTIONS=-Wall -Wextra -pedantic
OBJECTS=abuf.o file.o helper.o input.o kilo.o output.o terminal.o

run: kilo
	./kilo

kilo: $(OBJECTS)
	$(CC) $(OPTIONS) $(OBJECTS) -o kilo

abuf.o: abuf.c abuf.h
	$(CC) $(OPTIONS) -c abuf.c

file.o: file.c file.h abuf.h helper.h
	$(CC) $(OPTIONS) -c file.c

helper.o: helper.c helper.h
	$(CC) $(OPTIONS) -c helper.c

input.o: input.c input.h file.h helper.h output.h
	$(CC) $(OPTIONS) -c input.c

kilo.o: kilo.c file.h helper.h input.h output.h terminal.h
	$(CC) $(OPTIONS) -c kilo.c

output.o: output.c output.h abuf.h file.h helper.h
	$(CC) $(OPTIONS) -c output.c

terminal.o: terminal.c terminal.h helper.h
	$(CC) $(OPTIONS) -c terminal.c

clean:
	rm -f $(OBJECTS) kilo
