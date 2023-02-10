# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clecat <clecat@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/20 11:44:23 by clecat            #+#    #+#              #
#    Updated: 2023/02/10 17:25:48 by clecat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g #-fsanitize=address
NAME	= minishell
LIBPATH	= ~/.brew/Cellar/readline/8.2.1/lib/ 
SRC		=	main.c \
		exec.c \
		exec_utils.c \
		Built-in/cd.c \
		Built-in/cd_utils.c \
		Built-in/cd_tild.c \
		Built-in/echo.c \
		Built-in/env.c \
		Built-in/exit_pwd_utils.c \
		Built-in/exit_pwd.c \
		Built-in/export_addvar.c \
		Built-in/export.c \
		Built-in/export_change_val.c \
		Built-in/export_utils.c \
		Built-in/unset.c \
		Built-in/signals.c \
		Built-in/signaux.c \
		Built-in/annexe.c \
		Parse/init.c \
		Parse/lexer.c \
		Parse/gestion_dollar.c \
		Parse/gestion_dollar_line.c \
		Parse/gestion_dollar_utils.c \
		Parse/gestion_dollar_utils2.c \
		Parse/gestion_dollar_quotes.c \
		Parse/modif_tcmd.c \
		Parse/parse.c \
		Parse/pipe_utils.c \
		Parse/pipe.c \
		Parse/redir_utils.c \
		Parse/redir_utils2.c \
		Parse/redir.c \
		Parse/splitcmd_utils1.c \
		Parse/splitcmd_utils2.c \
		Parse/splitcmd_valid.c \
		Parse/splitcmd.c \
		Parse/splitline_utils.c \
		Parse/splitline.c \
		Parse/verif_cotes.c \
		Parse/verif_cotes_utils.c \
		Parse/check_cmd.c \
		Parse/verif_pipes.c \
		Parse/utils.c \
		Utils/ft_split.c \
		Utils/ft_itoa.c \
		Utils/utils.c \
		Utils/utils2.c \
		Utils/utils3.c \
		Utils/printstruc.c 

OBJ		= $(SRC:.c=.o)

all		: ${NAME}

$(NAME)	: ${OBJ} 
		@echo "\033[1;35m""Compilation de ${NAME}"
		$(CC) $(OBJ) $(CFLAGS) -lreadline -L $(LIBPATH) -o $(NAME)

%.o		: %.c
		@echo "\033[1;35m""Compilation des fichiers sources"
		$(CC) -c $< -o $@ $(CFLAGS) -I.

clean 	:
		@echo "\033[1;34m""Suppression des .o de ${NAME}"
		rm -rf $(OBJ)

fclean	:	clean
		@echo "\033[1;34m""Supression de l'executable..."
		rm -rf $(NAME)

norme	:
	norminette -R CheckForbiddenSourceHeader | grep -v OK || true
	@rm -rf $(OBJ)
	@echo "used functions that may be forbidden"
	@nm -u minishell | egrep -v "readline|rl_clear_history|rl_on_new_line" \
	| egrep -v "rl_replace_line|rl_redisplay|add_history|printf|malloc|free" \
	| egrep -v "write|access|open|read|close|fork|wait|waitpid|wait3|wait4" \
	| egrep -v "signal|sigaction|sigemptyset|sigaddset|kill|exit|getcwd" \
	| egrep -v "chdir|stat|lstat|fstat|unlink|execve|dup|dup2|pipe|opendir" \
	| egrep -v "readdir|closedir|strerror|perror|isatty|ttyname|ttyslot" \
	| egrep -v "ioctl|getenv|csuetattr|tcgetattr|tgetent|tgetflag" \
	| egrep -v "tgetnum|tgetstr|tgoto|tputs|dyld_stub_binder" || true

re	:	fclean all

.PHONY:	all clean fclean re
