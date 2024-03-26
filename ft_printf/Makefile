# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/14 16:05:51 by pzurawic          #+#    #+#              #
#    Updated: 2024/03/14 18:08:13 by pzurawic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -fr

FILES = ft_printf \
		ft_printf_format_specifier \
		ft_printf_c \
		ft_printf_id \
		ft_printf_p \
		ft_printf_s \
		ft_printf_u \
		ft_printf_xx 

LIBFT_DIR = ./libft

LIBFT_SRCS_FILES = $(wildcard $(LIBFT_DIR)/*.c)

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES))) $(LIBFT_SRCS_FILES:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
