NAME := a.out

SRC := microshell.c

OBJ := $(SRC:%.c= %.o)

CC = gcc -g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) -o $@
	@echo "$(NAME) has been compiled"

%.o: %.cpp
	@$(CC) -c $< $(CFLAGS) -o $@
	@echo "$@ has been compiled"

clean:
	@rm -rf $(OBJ)
	@echo "Object files has been deleted"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(NAME) has been deleted"

re: fclean all

.PHONY: all clean fclean re