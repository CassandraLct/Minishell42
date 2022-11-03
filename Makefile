CC		= GCC
CFLAGS	= -Wall -Wextra -Werror #-g -fsanitize=address
NAME	= minishell
LIBPATH = ~/.brew/Cellar/readline/8.2.1/lib
SRC		= src/main.c 

OBJ		= $(SRC:.c=.o)

all : $(NAME)

%.o : %.c
	@echo "\033[1;35m""Compilation de ${Name}..."
	$(CC) -o $@ -c $< $(CFLAGS)

$(NAME) : $(OBJ)
	@echo "\033[1;35m""Compilation de ${NAME}..."
	$(CC) $(OBJ) $(CFLAGS) -lreadline -L $(LIBPATH) -o $(NAME)

clean :
	@echo "\033[1;35m""Compilation de ${NAME}..."
	rm -rf $(OBJ)

fclean : clean
	@echo "\033[1;34m""Supression des executables et librairies..."
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re