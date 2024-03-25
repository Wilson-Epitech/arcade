##
## ARCADE PROJECT, 2023
## arcade_sfml.so
## File description:
## Makefile
##

SRC =	./LibSfml.cpp

OBJ = $(SRC:.cpp=.o)

CXX = g++

CXXFLAGS = -Wall -Wextra -lsfml-graphics -fPIC

LDFLAGS = -shared

FLAGS_DEBUG = -g3

BIN_NAME = arcade_sfml.so

all: $(OBJ)
	$(CXX) -c $(CXXFLAGS) $(SRC)
	$(CXX) $(LDFLAGS) -o $(BIN_NAME) $(OBJ)
	mv $(BIN_NAME) ../../

debug: CFLAGS += $(FLAGS_DEBUG)
debug: all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(BIN_NAME)

re: fclean all

.PHONY: clean fclean re
