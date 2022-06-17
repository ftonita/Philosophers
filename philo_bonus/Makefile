NAME = philosophers_bonus
SRCS		=	philosophers.c	valid+init.c		utils.c	\
				launch.c		routine_philo.c		checker.c		free_funcs.c

OBJ		=	$(SRCS:%.c=%.o)

HEADER	=	philosophers.h

CC		=	gcc

FLAGS	=	-Wall -Wextra -Werror -g

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