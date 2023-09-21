CC = gcc
EXEC = start
OBJ = main.o menu.o simulation.o pile.o
SRC = main.c

all: $(EXEC)
    rm -rf *.o
    ./$(EXEC)

main.o : main.c
    $(CC) -o main.o -c main.c

menu.o : menu.h menu.c
    $(CC) -o menu.o  -c menu.c

simulation.o : simulation.h simulation.c
    $(CC) -o simulation.o  -c simulation.c

pile.o : pile.c
    $(CC) -o pile.o  -c pile.c

$(EXEC) : $(OBJ)
    $(CC) -o $(EXEC) main.o menu.o simulation.o pile.o

clean :
    rm -rf *.o