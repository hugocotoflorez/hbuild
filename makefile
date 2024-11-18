INCL = ./include
SRC = ./src/*.c
FLAGS = -Wall -Wextra -fsanitize=address,null -O0 -g
CC = gcc

all:
	 $(CC) $(SRC) $(FLAGS) -I $(INCL) -o hbuild
	 ./hbuild install
