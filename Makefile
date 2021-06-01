# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/27 11:22:54 by mmunoz-f          #+#    #+#              #
#    Updated: 2021/06/01 08:39:16 by pgomez-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TIME =   $(shell date +'%d/%m/%Y %H:%M:%S')
M =
CC = clang
#CFLAGS = -Wall -Wextra -Werror -g
NAME = koala
SOURCE = koala.c read_check.c manipulate_line.c lexer.c check_lexer.c parser.c ko_utils.c queue/queue.c
OBJS_SOURCE = $(SOURCE:.c=.o)
LIBFT_PATH = libft

all: $(NAME)

libft/libft.a:
	make -C ./libft

$(NAME): libft/libft.a $(OBJS_SOURCE)
	$(CC) $(CFLAGS) -o $@ $(OBJS_SOURCE) -L$(LIBFT_PATH) -lft

clean:
	rm -f $(OBJS_SOURCE) $(OBJS_BONUS)
	make fclean -C ./libft

fclean: clean
	rm -f $(NAME)

re: fclean all

push: fclean
	git add .
	git commit -m "$(TIME) - $(M)"
	git push

.PHONY: all clean fclean re bonus push
