NAME = philo

CC = cc

CFLAGS = -Werror -Wextra -Wall

SRC := clean_memory.c death_check.c ft_atoi.c init.c main.c parse_args.c simulation.c time_handling.c

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