NAME = philo
CC = clang
CFLAGS = -Wall -Werror -Wextra -pthread -fsanitize=thread -g

SRC_PATH = sources/
OBJ_PATH = objects/

SRC = activities.c forks_and_philos.c input_checker.c \
		one_philo_case.c philo.c simulation_utils.c \
		simulation.c utils.c

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

INC = -I ./includes/

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean clean

.PHONY: all re clean fclean