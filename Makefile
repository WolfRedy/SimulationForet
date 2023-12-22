CC = gcc
TARGET = fire-emul
SRC_DIR = main core simulation GUI
SRC = $(wildcard $(addsuffix /*.c, $(SRC_DIR)))
OBJ = $(SRC:.c=.o)

CFLAGS = 

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) -ggdb -lm -lncurses `pkg-config --cflags --libs gtk+-3.0`

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@  -ggdb -lm -lncurses `pkg-config --cflags --libs gtk+-3.0`

clean:
	rm -rf $(OBJ) $(TARGET)
