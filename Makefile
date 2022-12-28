# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/20 11:44:23 by clecat            #+#    #+#              #
#    Updated: 2022/12/27 15:00:13 by rdi-marz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g #-fsanitize=address
NAME	= minishell
LIBPATH	= ~/.brew/Cellar/readline/8.2.1/lib/
SRC	=	main.c parse/parse.c utils/utils.c built-in/env.c built-in/export.c built-in/export_utils.c \
		built-in/export_addvar.c built-in/export_change_val.c built-in/exit_pwd.c parse/init.c exec.c \
		utils/ft_split.c parse/lexer.c built-in/echo.c built-in/unset.c built-in/cd.c built-in/cd_utils.c \
		built-in/signaux.c

OBJ	= $(SRC:.c=.o)

all	:	${NAME}

$(NAME)	:	${OBJ}
		@echo "\033[1;35m""Compilation de ${NAME}"
		$(CC) $(OBJ) $(CFLAGS) -lreadline -L $(LIBPATH) -o $(NAME)

%.o	:	%.c
		@echo "\033[1;35m""Compilation des fichiers sources"
#		@$(CC) $(CFLAGS) -Imlx -c $< -o $@
		$(CC) -o $@ -c $< $(CFLAGS) 

clean :
		@echo "\033[1;34m""Suppression des .o de ${NAME}"
		rm -rf $(OBJ)

fclean	:	clean
		@echo "\033[1;34m""Supression de l'executable..."
		rm -rf $(NAME)

re	:	fclean all

.PHONY:	all clean fclean re