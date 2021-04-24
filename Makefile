SRC=src/main.c src/state.c src/graphics.c src/resources.c

OBJ=$(SRC:.c=.o)
CFLAGS=-g -Werror -Wextra -Wall `pkg-config --cflags sdl2 SDL2_gfx SDL2_mixer`
LDFLAGS=`pkg-config --libs sdl2 SDL2_gfx SDL2_mixer` -lm
TARGET=digger
CC=gcc
LD=gcc

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(LD) $^ -o $@ $(LDFLAGS)

.c.o:
	$(CC) -c $^ -o $@ $(CFLAGS)

clean:
	$(RM) $(TARGET) $(OBJ)
