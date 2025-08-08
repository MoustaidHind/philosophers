NAME = philo

CC = cc

CFLAGS = -Werror -Wextra -Wall -fsanitize=thread -g

SRC := $(wildcard *.c) # change it in other time

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean : 
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: fclean clean re all

.SECONDARY: $(OBJ)