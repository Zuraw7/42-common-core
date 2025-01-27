NAME = interfaces

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRC_PATH = sources/
SRC = $(wildcard $(SRC_PATH)*.cpp)
OBJ_PATH = obj/
OBJ = $(patsubst $(SRC_PATH)%.cpp, $(OBJ_PATH)%.o, $(SRC))

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all
