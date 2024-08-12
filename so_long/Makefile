NAME = so_long

CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -Iincludes/mlx -Lincludes/mlx
LIBFT = includes/libft/libft.a

RM = rm -fr

SRC_DIRS = enemies_handling keyboard_events map_error_handlings map_handling stats animations

SRCS = $(wildcard so_long.c $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c)))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) -Lincludes/libft -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C includes/libft

clean:
	$(RM) $(OBJS)
	make -C includes/libft clean

fclean: clean
	$(RM) $(NAME)
	make -C includes/libft fclean

re: fclean all

.PHONY: all clean fclean re
