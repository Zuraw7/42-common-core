NAME = phonebook
GCC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98

SRCSDIR = class_code
INCDIR = class_headers
OBJDIR = obj

SRCS = $(wildcard $(SRCSDIR)/*.cpp) main.cpp
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(GCC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "Compiled $(NAME) successfully!"

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)/class_code
	@$(GCC) $(FLAGS) -I$(INCDIR) -c $< -o $@
	@echo "Compiled $< -> $@"

clean:
	rm -rf $(OBJDIR)
	@echo "Cleaned object files."

fclean: clean
	rm -rf $(NAME)
	@echo "Cleaned $(NAME)."

re: fclean all
