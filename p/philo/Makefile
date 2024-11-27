SOURCE = philo.c utils.c parsing.c philo_utils.c philo_utils_2.c philo_utils_3.c 

OBJ = $(SOURCE:.c=.o)

CC = cc 
CFLAGS = -Wall -Wextra -Werror 

NAME = philo

RM =rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@
clean: 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
