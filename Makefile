CC = gcc
TARGET = fire
SRC_DIR = main core simulation
SRC = $(wildcard $(addsuffix /*.c, $(SRC_DIR)))
OBJ = $(SRC:.c=.o)

CFLAGS = 

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) -ggdb -lncurses `pkg-config --cflags --libs gtk+-3.0`

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@  -ggdb -lncurses `pkg-config --cflags --libs gtk+-3.0`

clean:
	rm -rf $(OBJ) $(TARGET)
