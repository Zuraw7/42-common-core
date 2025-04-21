NAME = push_swap
BONUS_NAME = checker
CC = clang
CFLAGS = -Wall -Wextra -Werror -g

SRC_PATH = sources/
OBJ_PATH = objects/

LIBFT = includes/libft/libft.a

SRC = $(wildcard $(SRC_PATH)*.c $(SRC_PATH)nodes/*.c $(SRC_PATH)stacks/*.c $(SRC_PATH)operations/*.c $(SRC_PATH)parser/*.c $(SRC_PATH)sort/*.c)
BONUS_SRC = bonus/checker.c

OBJ = $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRC))
BONUS_OBJ = bonus/checker.o

BONUS_OBJ_FILTERED = $(filter-out $(OBJ_PATH)main.o, $(OBJ))

INC = -I ./includes/ -I ./includes/libft/

all: $(LIBFT) $(NAME)
	@echo "Test push_swap like this:"
	@echo 'ARG="$$(seq -1000 1000 | shuf -n 500)"; ./push_swap $$ARG | wc -l'
	@echo 'ARG="$$(seq -1000 1000 | shuf -n 500)"; ./push_swap $$ARG | ./checker $$ARG'

$(LIBFT):
	make -C ./includes/libft/

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $@ $(INC)

bonus: $(LIBFT) $(BONUS_NAME)

$(BONUS_OBJ): $(BONUS_SRC)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(BONUS_NAME): $(BONUS_OBJ) $(BONUS_OBJ_FILTERED)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(BONUS_OBJ_FILTERED) $(LIBFT) -o $@ $(INC)

clean:
	rm -rf $(OBJ_PATH) $(BONUS_OBJ)
	make clean -C ./includes/libft/

fclean: clean
	rm -rf $(NAME) $(BONUS_NAME)
	make fclean -C ./includes/libft/

re: fclean all

.PHONY: all bonus re clean fclean
