NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC
AR = ar rcs
RM = rm -f

FILES = ft_atoi \
		ft_bzero \
		ft_calloc \
		ft_isalnum \
		ft_isalpha \
		ft_isascii \
		ft_isdigit \
		ft_isprint \
		ft_itoa \
		ft_memchr \
		ft_memcmp \
		ft_memcpy \
		ft_memmove \
		ft_memset \
		ft_putchar_fd \
		ft_putendl_fd \
		ft_putnbr_fd \
		ft_putstr_fd \
		ft_split \
		ft_strchr \
		ft_strdup \
		ft_striteri \
		ft_strjoin \
		ft_strlcat \
		ft_strlcpy \
		ft_strlen \
		ft_strmapi \
		ft_strncmp \
		ft_strnstr \
		ft_strrchr \
		ft_strtrim \
		ft_substr \
		ft_tolower \
		ft_toupper \
		ft_printf \
		ft_printf_c \
		ft_printf_format_specifier \
		ft_printf_id \
		ft_printf_p \
		ft_printf_s \
		ft_printf_u \
		ft_printf_xx \
		get_next_line \
		get_next_line_utils

FILES_B = 	ft_lstnew_bonus \
	  		ft_lstadd_front_bonus \
	  		ft_lstsize_bonus \
	  		ft_lstlast_bonus \
	  		ft_lstadd_back_bonus \
	  		ft_lstdelone_bonus \
	  		ft_lstclear_bonus \
	  		ft_lstiter_bonus \
	  		ft_lstmap_bonus

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
SRCS_B = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES_B)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
OBJS_B = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES_B)))

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: $(OBJS_B)
	$(AR) $(NAME) $(OBJS_B)

m: $(NAME)

all: m bonus

clean:
	$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
