# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgomez-a <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/26 09:56:35 by pgomez-a          #+#    #+#              #
#    Updated: 2021/05/26 09:56:37 by pgomez-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:	all run clean fclean re

NAME	= prompt

SRCS	= main.c			\
		  ./queue/queue.c

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
	@make clean -C ./libft/
	@$(RM) $(OBJS)

fclean:		clean
	@make fclean -C ./libft/
	@$(RM) $(NAME)

re:		fclean all

