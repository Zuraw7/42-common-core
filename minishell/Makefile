NAME = minishell
CC = clang
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline -ltermcap -lncurses -L ./includes/libft/ -lft

SRC_PATH = sources/
OBJ_PATH = objects/

LIBFT = includes/libft/libft.a

SRC = $(wildcard $(SRC_PATH)*.c $(SRC_PATH)utils/*.c $(SRC_PATH)parsing/*.c $(SRC_PATH)exec/*.c $(SRC_PATH)exec/temp_src_exec/temp_src_func.c $(SRC_PATH)builtins/*.c)

OBJ = $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRC))

INC = -I ./includes/ -I ./includes/libft/

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C ./includes/libft/

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

clean:
	rm -rf $(OBJ_PATH)
	make clean -C ./includes/libft/

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./includes/libft/

re: fclean all

.PHONY: all re clean fclean
