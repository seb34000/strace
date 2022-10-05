##
## EPITECH PROJECT, 2022
## exemple
## File description:
## Makefile
##

NAME    =       strace

CC      =       gcc -g3

SRC     =       $(wildcard ./src/*.c)

OBJ     =       $(SRC:.c=.o)

OBJD     =       $(TEST:.c=.o)

CFLAGS  =       -I include -Wall -Wextra -Wno-missing-braces


all:    $(NAME)

$(NAME):        $(OBJ)
	$(CC)$(INCLUDE) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAMED)
	rm -f ./*.o
	rm -f ./a.out

re:     fclean all