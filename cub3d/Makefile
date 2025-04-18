# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alicja <alicja@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/03 10:48:32 by astefans          #+#    #+#              #
#    Updated: 2025/04/13 21:21:06 by alicja           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -g3

MLX = $(MLX_PATH)/libmlx.a
MLX_PATH = includes/minilibx
MLXFLAGS = -Lincludes/minilibx -lm -lmlx -L/usr/lib/X11 -lXext -lX11

LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_PATH = includes/libft

NAME = cub3d
SRC_PATH = sources/
SRC =	$(wildcard $(SRC_PATH)*.c \
		$(SRC_PATH)move-events/*.c \
		$(SRC_PATH)window_management/*.c \
		$(SRC_PATH)utils/*.c \
		$(SRC_PATH)map_reader/*.c \
		$(SRC_PATH)raycasting/*.c )

OBJ_PATH = objects/
OBJ = $(SRC:$(SRC_PATH)%.c=%.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

INCLUDE_DIR = includes

OBJ_DIRS = $(sort $(dir $(OBJS)))

RM = rm -rf

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_DIRS) # Tworzenie wszystkich potrzebnych podkatalogów
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_DIR)

$(MLX):
	@make -C $(MLX_PATH)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLXFLAGS)

clean:
	$(RM) $(OBJ_PATH)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
