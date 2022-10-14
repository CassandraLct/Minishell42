CC		= GCC
CFLAGS	= -Wall -Wextra -Werror
NAME	= minishell
SRC		=

OBJ		= $(SRC:.c=.o)

all : $(NAME)

%.o : %.c

$(NAME) : $(OBJ)

clean :

fclean : clean

re : fclean all

.PHONY : all clean fclean re