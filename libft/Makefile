NAME	=	libft.a

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra

SRC		=	$(wildcard */*.c)


OBJ		=	$(SRC:.c=.o)
H		=	libft.h

RM		=	rm -rf

.PHONY:	all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o : %.c $(H)
	$(CC) -I . $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
