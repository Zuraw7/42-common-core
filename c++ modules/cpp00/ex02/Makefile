NAME = gbu
GCC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = tests.cpp Account.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(GCC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
