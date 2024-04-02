NUM_COLORS ?= 5
NUM_LEVELS ?= 2
NUM_TOKENS ?= 25
MUNIFICENCE_FLAGS = -DNUM_COLORS=$(NUM_COLORS) -DNUM_LEVELS=$(NUM_LEVELS) -DNUM_TOKENS=$(NUM_TOKENS)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MUNIFICENCE_FLAGS) -I$(SRC)

CC = gcc
all: project test

OBJ= color.o \
builder.o \
token.o \
guild.o \
market.o \
player.o\
test_color.o \
test_builder.o \
test_token.o \
test_guild.o \
test_market.o \
test_player.o\
test_all.o \

PROJ=color.o \
builder.o \
token.o \
guild.o \
market.o \
player.o \
project.o \

PROJ2=color.o \
builder.o \
token.o \
guild.o \
market.o \
player.o \
project2.o \

PLAY= color.o\
builder.o\
token.o\
market.o\
guild.o\
player.o\

SRC=./src
TST=./tst

market.h : token.h
token.h : color.h
market.c : market.h
color.c : color.h
guild.c : guild.h
guild.h : builder.h 
player.c : player.h 
player.h : guild.h 
player.h : market.h 
project.c : project.h
test_all.c : test_all.h

%.o: $(SRC)/%.c
	$(CC) -c $(CFLAGS) $<

%.o: $(TST)/%.c
	$(CC) -c -I$(TST) $(CFLAGS) $<

%.o: %.c
	$(CC) -c $(CFLAGS) $<

test: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o test

project: $(PROJ)
	$(CC) $(CFLAGS) $(PROJ) -o project

project2: $(PROJ2)
	$(CC) $(CFLAGS) $(PROJ2) -o project2
player: $(PLAY)
	$(CC) $(CFLAGS) $(PLAY) -o player

clean:
	rm -f project test_project *.o *~
