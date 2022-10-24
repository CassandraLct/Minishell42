CC		= GCC
CFLAGS	= -Wall -Wextra -Werror -g #-fsanitize=address
NAME	= minishell
#LIBPATH = ~/.brew/opt/readline/include/readline
SRC		= src/main.c 

OBJ		= $(SRC:.c=.o)


all : $(NAME)

%.o : %.c
	@echo "\033[1;35m""Compilation de ${Name}..."
	$(CC) -o $@ -c $< $(CFLAGS)

$(NAME) : $(OBJ)
	@echo "\033[1;35m""Compilation de ${NAME}..."
	$(CC) $(OBJ) $(CFLAGS) libreadline.a -lreadline -lncurses -o $(NAME)

clean :
	@echo "\033[1;35m""Compilation de ${NAME}..."
	rm -rf $(OBJ)

fclean : clean
	@echo "\033[1;34m""Supression des executables et librairies..."
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re