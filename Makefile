CC = cc
NAME = pipex
CFLAGS = -Wall -Wextra -Werror
SRC = pipex_bonus.c ft_split_bonus.c get_next_line_utils.c get_next_line.c \
		helper_function_bonus.c helper_function2_bonus.c printf.c helper_function3_bonus.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

bonus: all

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(LIB_PATH) -o $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

ra: all clean

.PHONY: all bonus clean fclean