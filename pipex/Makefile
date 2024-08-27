NAME = pipex
NAME_BONUS = pipex_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT = includes/libft/libft.a

RM = rm -fr

SRCS = pipex.c path_finder.c cmd_utils.c cmd_runner.c
SRCS_BONUS = bonus/pipex_bonus.c bonus/path_finder_bonus.c bonus/cmd_utils_bonus.c bonus/cmd_runner_bonus.c bonus/here_doc_bonus.c bonus/utils_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -Lincludes/libft -lft -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -Lincludes/libft -lft -o $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C includes/libft

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	make -C includes/libft clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	make -C includes/libft fclean

re: fclean all

.PHONY: all clean fclean re