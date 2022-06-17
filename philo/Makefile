NAME = philosophers
SRCS = philosophers.c routine_philo.c utils.c init.c custom.c\

OBJ		=	$(SRCS:%.c=%.o)

HEADER	=	philosophers.h

CC		=	gcc

FLAGS	=	-Wall -Wextra -Werror -g# -fsanitize=thread

RM		=	rm -rf

test:	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o:		%.c $(HEADER)
			$(CC) $(FLAGS)  -c $< -o $@ -MD
clean:
			@$(RM) $(OBJ)
			@$(RM) *.d

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all	clean	fclean	re	libft