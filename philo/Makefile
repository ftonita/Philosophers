NAME = philosophers
SRCS = philosophers.c utils.c\

OBJ		=	$(SRCS:%.c=%.o)

HEADER	=	philosophers.h

CC		=	gcc

FLAGS	=	-Wall -Wextra -Werror

RM		=	rm -rf

test:	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) $(OBJ) -o $(NAME)

# %.o:		%.c $(HEADER)
# 			$(CC) $(FLAGS)  -c $< -o $@

clean:
			@$(RM) $(OBJ)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all	clean	fclean	re	libft