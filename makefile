INCL = ./include
SRC = ./src/*.c
FLAGS = -O3
CC = gcc

all:
	 $(CC) $(SRC) $(FLAGS) -I $(INCL) -o hbuild
