TIME =   $(shell date +'%d/%m/%Y %H:%M:%S')

M =
BRANCH =

CC = clang
CFLAGS = -g
#CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
NAME = koala

SOURCE = koala.c				\
	ko_utils.c				\
	manipulate_line.c			\
	queue/queue.c				\
	dlists/dlists.c				\
	dlists/more_dlists.c			\
	lexer/lexer.c lexer/check_lexer.c	\
	parser/parser.c				\
	parser/expand.c				\
	executor/pipe_executor.c			\
	executor/find_cmd.c			\
	executor/find_red.c			\
	executor/signal.c			\
	reader/read_cmds.c			\
	reader/termcaps_op.c			\
	reader/koala_history.c		\
	builtins/exec_builtins.c	\
	builtins/cd_builtin.c		\
	builtins/export_builtin.c	\
	builtins/export_builtin_utils.c	\
	builtins/unset_builtin.c

OBJS_SOURCE = $(SOURCE:.c=.o)

LIBFT_PATH = libft

all: $(NAME)

libft/libft.a:
	make -C ./libft

$(NAME): libft/libft.a $(OBJS_SOURCE)
	$(CC) $(CFLAGS) -o $@ $(OBJS_SOURCE) -L$(LIBFT_PATH) -lft -ltermcap

clean:
	rm -f $(OBJS_SOURCE) $(OBJS_BONUS) /tmp/.koala_history /tmp/.koala_heredoc
	make fclean -C ./libft

fclean: clean
	rm -f $(NAME)

re: fclean all

push: fclean
	git add .
	git commit -m "$(TIME) - $(M)"
	git push

push_to_main: push
	git checkout main
	git pull origin $(BRANCH)
	git push
	git checkout $(BRANCH)

.PHONY: all clean fclean re bonus push
