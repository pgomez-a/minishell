TIME =   $(shell date +'%d/%m/%Y %H:%M:%S')

M =

CC = clang
CFLAGS = -g -fsanitize=address
#CFLAGS = -Wall -Wextra -Werror
NAME = koala

SOURCE = koala.c							\
	ko_utils.c								\
	manipulate_line.c						\
	queue/queue.c							\
	dlists/dlists.c							\
	dlists/more_dlists.c					\
	parser/check_prompt.c					\
	lexer/lexer.c lexer/check_lexer.c		\
	parser/parser.c parser/check_parser.c	\
	reader/read_cmds.c						\
	reader/termcaps_op.c					\
	reader/check_line.c						\
	reader/koala_history.c
	#read_prompt.c

OBJS_SOURCE = $(SOURCE:.c=.o)

LIBFT_PATH = libft

all: $(NAME)

libft/libft.a:
	make -C ./libft

$(NAME): libft/libft.a $(OBJS_SOURCE)
	$(CC) $(CFLAGS) -o $@ $(OBJS_SOURCE) -L$(LIBFT_PATH) -lft -ltermcap

clean:
	rm -f $(OBJS_SOURCE) $(OBJS_BONUS) .koala_history
	make fclean -C ./libft

fclean: clean
	rm -f $(NAME)

re: fclean all

push: fclean
	git add .
	git commit -m "$(TIME) - $(M)"
	git push

.PHONY: all clean fclean re bonus push
