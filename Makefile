##
## ARCADE PROJECT, 2023
## test
## File description:
## Makefile
##

SRC = ./src/main.cpp

OBJ = $(SRC:.cpp=.o)

CFLAGS = -Wall -Wextra -I lib/graphical -lsfml-graphics -lSDL2 -lSDL2_ttf

FLAGS_DEBUG = -g3

BIN_NAME = arcade

CC = g++

debug: CFLAGS += $(FLAGS_DEBUG)
debug: all

graphicals:
	cd ./lib/graphical/lib_sfml/ && make
	cd ./lib/graphical/lib_sdl/ && make

all: $(OBJ)	graphicals
	$(CC) -o $(BIN_NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(BIN_NAME)

re: fclean all

.PHONY: clean fclean re
