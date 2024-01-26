##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC =	src/main.cpp

OBJ = $(SRC:.cpp=.o)

NAME = MyGKrellm

CXXFLAGS += -Wall -Wextra -std=c++20

CPPFLAGS += -I./include

.DEFAULT_GOAL =	all

all: $(NAME)
$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
