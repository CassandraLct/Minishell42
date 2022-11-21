CC		= GCC
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address
NAME	= minishell
LIBPATH = ~/.brew/Cellar/readline/8.2.1/lib
SRC		= main.c parse.c utils.c built-in/env.c built-in/export.c built-in/export_utils.c \
		built-in/cd.c built-in/exit_pwd.c init.c #built-in/echo.c

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