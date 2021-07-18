NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I includes/

LIBFT = -L. -lft

SRC_DIR = src/

SRC_LIST = 	philo.c \
			libft.c \
			utils.c \
			activity.c

SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n"
	@echo "\033[0;33mCompiling philo..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "\n\033[0;32m* * * SUCCESS * * *\n"
	@echo "\033[0;32mCreated file philo\n"

%.o: %.c
	@printf "\n\033[0;33mGenerating philo objects... %-33.33s\r" $@
	@${CC} -g ${CFLAGS} -c $< -o $@

clean:
	@echo "\n\033[0;31mRemoving binaries..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@echo "\n\033[0;31mDeleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\nDeleting trash..."
	@rm -f *.txt
	@rm -f *.out
	@echo "\033[0m"

re: fclean all

test: all
	./$(NAME)

norm:
	norminette $(SRC) includes/$(HEADER)

.PHONY: clean fclean re test norm
