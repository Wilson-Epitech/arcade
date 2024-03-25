##
## ARCADE PROJECT, 2023
## test
## File description:
## Makefile
##

SRC = ./src/core.cpp

OBJ = $(SRC:.cpp=.o)

CFLAGS = -Wall -Wextra -I lib/graphical -lsfml-graphics -lSDL2 -lSDL2_ttf -lncurses

FLAGS_DEBUG = -g3

BIN_NAME = arcade

CC = g++

debug: CFLAGS += $(FLAGS_DEBUG)
debug: all

core: $(OBJ)
	$(CC) -o $(BIN_NAME) $(OBJ) $(CFLAGS)

graphicals:
	cd ./lib/graphical/libSfml/ && make re
	cd ./lib/graphical/libSdl/ && make re
	cd ./lib/graphical/libNcurses/ && make re

games:
	cd ./lib/games/pacman/ && make re

all: $(OBJ)	graphicals games
	$(CC) -o $(BIN_NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(BIN_NAME)

re: fclean all

.PHONY: clean fclean re
