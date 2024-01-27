##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC =  $(wildcard src/*.cpp)
SRC += $(wildcard src/*/*.cpp)

OBJ = $(SRC:.cpp=.o)

NAME = MyGKrellm

CXXFLAGS += -Wall -Wextra -std=c++20

CPPFLAGS += -iquoteinclude

.DEFAULT_GOAL =	all

all: $(NAME)
$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.NOTPARALLEL: re

.PHONY: all clean fclean re
