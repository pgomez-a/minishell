TIME =   $(shell date +'%d/%m/%Y %H:%M:%S')

M =
BRANCH =

CC = clang
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
NAME = koala

SRC_PATH = srcs
OBJ_PATH = objs

SRCS = $(SRC_PATH)/koala.c				\
	$(SRC_PATH)/utils/ko_utils.c			\
	$(SRC_PATH)/utils/simple_utils.c		\
	$(SRC_PATH)/manipulate_line.c			\
	$(SRC_PATH)/queue/queue.c				\
	$(SRC_PATH)/dlists/dlists.c				\
	$(SRC_PATH)/dlists/more_dlists.c			\
	$(SRC_PATH)/lexer/lexer.c					\
	$(SRC_PATH)/lexer/check_lexer.c			\
	$(SRC_PATH)/parser/parser.c				\
	$(SRC_PATH)/parser/expand.c				\
	$(SRC_PATH)/executor/executor.c			\
	$(SRC_PATH)/executor/find_cmd.c			\
	$(SRC_PATH)/executor/find_red.c			\
	$(SRC_PATH)/executor/signal.c			\
	$(SRC_PATH)/executor/manege_pipe.c		\
	$(SRC_PATH)/reader/read_cmds.c			\
	$(SRC_PATH)/reader/termcaps_op.c			\
	$(SRC_PATH)/reader/koala_history.c		\
	$(SRC_PATH)/builtins/exec_builtins.c	\
	$(SRC_PATH)/builtins/cd_builtin.c		\
	$(SRC_PATH)/builtins/export_builtin.c	\
	$(SRC_PATH)/builtins/export_builtin_utils.c	\
	$(SRC_PATH)/builtins/unset_builtin.c	\
	$(SRC_PATH)/parser/split_expand.c

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

OBJS = $(SRCS:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

LIBFT_PATH = ./srcs/libft

all: $(NAME)

libft/libft.a:
	make -C $(LIBFT_PATH)

$(OBJ_PATH):
	mkdir -p objs/utils objs/queue objs/dlists objs/lexer objs/parser objs/executor objs/reader objs/builtins

$(NAME): libft/libft.a $(OBJ_PATH) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -L$(LIBFT_PATH) -lft -ltermcap

clean:
	rm -rf $(OBJ_PATH) /tmp/.koala_history /tmp/.koala_heredoc
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
