TIME =   $(shell date +'%d/%m/%Y %H:%M:%S')

M =

CC = clang
CFLAGS = -g
#CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
NAME = koala

SOURCE = koala.c					\
	 check_prompt.c					\
	 manipulate_line.c				\
	 lexer.c check_lexer.c			\
	 parser.c check_parser.c		\
	 ko_utils.c						\
	 read_cmds.c					\
	 termcaps_op.c					\
	 queue/queue.c
	 #read_prompt.c

OBJS_SOURCE = $(SOURCE:.c=.o)

LIBFT_PATH = libft

all: $(NAME)

libft/libft.a:
	make -C ./libft

$(NAME): libft/libft.a $(OBJS_SOURCE)
	$(CC) $(CFLAGS) -o $@ $(OBJS_SOURCE) -L$(LIBFT_PATH) -lft -ltermcap

clean:
	rm -f $(OBJS_SOURCE) $(OBJS_BONUS) .history
	make fclean -C ./libft

fclean: clean
	rm -f $(NAME)

re: fclean all

push: fclean
	git add .
	git commit -m "$(TIME) - $(M)"
	git push

.PHONY: all clean fclean re bonus push
