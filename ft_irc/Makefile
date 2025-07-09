CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g -DDEBUG_MODE=0
RM = rm -rf
NAME = ircserv
SRC_DIR = src
INCLUDE_DIR = includes
OBJ_DIR = objects

# BONUS_SRC =
# BONUS_OBJ = $(SRC:%.cpp=$(BONUS_SRC_DIR)/%.o)

SRC = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/server/*.cpp $(SRC_DIR)/user/*.cpp $(SRC_DIR)/channel/*.cpp $(SRC_DIR)/exceptionIRC/*.cpp $(SRC_DIR)/membership/*.cpp)

OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)  # Tworzy wymagane katalogi dla plików obiektowych
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
