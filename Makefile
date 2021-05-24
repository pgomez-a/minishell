.PHONY:	all run clean fclean re

NAME	= prompt

SRCS	= main.c	\
	  get_command.c	\
	  ft_utils.c

OBJS	= $(SRCS:.c=.o)

LIB	= -L./libft/ -lft

CC 	= gcc

RM	= rm -f

$(NAME):	$(OBJS)
	@make -C ./libft/
	@gcc $(OBJS) $(LIB) -o $(NAME)

all:		$(NAME)

run:
	@./prompt

clean:
	@$(RM) $(OBJS)

fclean:		clean
	@$(RM) $(NAME)

re:		fclean all

