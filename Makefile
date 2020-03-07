CC=gcc
LD=$(CC)

CFLAGS=-Wall -Wextra -Iinclude -Werror -g 
LFLAGS=-lm

TARGET = slicer

SRC=$(wildcard source/*.c)
OBJ=$(SRC:.c=.o)

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(LD) $^ -o $@ $(LFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) $< -c -o $@

clean :
	find . -name "*~" -delete
	$(RM) $(OBJ) $(Target)
