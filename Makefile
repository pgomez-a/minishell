TIME =   $(shell date +'%d/%m/%Y %H:%M:%S')

M =
BRANCH =

CC = clang
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
NAME = koala

SOURCE = srcs/koala.c				\
	srcs/utils/ko_utils.c			\
	srcs/utils/simple_utils.c		\
	srcs/manipulate_line.c			\
	srcs/queue/queue.c				\
	srcs/dlists/dlists.c				\
	srcs/dlists/more_dlists.c			\
	srcs/lexer/lexer.c					\
	srcs/lexer/check_lexer.c			\
	srcs/parser/parser.c				\
	srcs/parser/expand.c				\
	srcs/executor/executor.c			\
	srcs/executor/find_cmd.c			\
	srcs/executor/find_red.c			\
	srcs/executor/signal.c			\
	srcs/executor/manege_pipe.c		\
	srcs/reader/read_cmds.c			\
	srcs/reader/termcaps_op.c			\
	srcs/reader/koala_history.c		\
	srcs/builtins/exec_builtins.c	\
	srcs/builtins/cd_builtin.c		\
	srcs/builtins/export_builtin.c	\
	srcs/builtins/export_builtin_utils.c	\
	srcs/builtins/unset_builtin.c

OBJS_SOURCE = $(SOURCE:.c=.o)

LIBFT_PATH = ./srcs/libft

all: $(NAME)

libft/libft.a:
	make -C ./srcs/libft

$(NAME): libft/libft.a $(OBJS_SOURCE)
	$(CC) $(CFLAGS) -o $@ $(OBJS_SOURCE) -L$(LIBFT_PATH) -lft -ltermcap

clean:
	rm -f $(OBJS_SOURCE) $(OBJS_BONUS) /tmp/.koala_history /tmp/.koala_heredoc
	make fclean -C ./srcs/libft

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
