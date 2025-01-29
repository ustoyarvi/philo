NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
SRC = src/cleanup.c src/init.c src/isimulation.c src/main.c src/monitor_routine.c src/philo_routine.c src/utils.c src/philo.h
OBJ = $(SRC:src/%.c=obj/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lpthread

obj/%.o : src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj/

fclean: clean
	rm -f $(NAME)

re: fclean all