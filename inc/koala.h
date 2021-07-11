/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   koala.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:24:53 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/06/03 08:23:51 by pgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KOALA_H
# define KOALA_H

# include <unistd.h>
# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <string.h>
# include "../srcs/libft/libft.h"
# include "../srcs/queue/queue.h"
# include "../srcs/dlists/dlists.h"

# define M_IMPLEMENTED_BUILTINS "pwd echo exit cd env export unset"

typedef struct s_cmd
{
	t_que			*cmd;
	t_que			*red;
	int				err;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_tty_info
{
	struct termios	read_tty_settings;
	t_dlist			*history;
	t_dlist			*strings;
	unsigned int	xcursor;
}	t_tty_info;

/**
 ** koala.c
 **/

t_tty_info	*init_terminal(t_tty_info *tty_info, int tty_mode);
void		set_prompt(void);

/**
 ** read_cmds.c
 **/

int			read_command_line(t_tty_info *tty_info);
void		add_character(t_tty_info *tty_info, char dst);

/**
 ** manipulate_line.c
 **/

void		man_command_line(t_dlist *history, char ***envp);

/**
 ** lexer.c
 **/

void		call_lexer(char *line, t_que **lex);

/**
 ** check_lexer.c
 **/

int			tokenize_pipe(char **tok, t_que **lex);
int			tokenize_quot(char quot, char *line, char **tok, t_que **lex);
int			tokenize_red(char *line, char **tok, t_que **lex);

/**
 ** parser.c
 **/

void		init_cmd(t_cmd **par);
void		call_parser(t_que **lex, t_cmd **par);

/**
 ** expand.c
 **/

void		call_env(t_cmd **par, char **envp);

/**
 ** split_expand.c
 **/

void		split_for_expansion(char **result, t_que **var);

/**
 ** executor.c
 **/

void		call_executor(t_dlist *history, char ***envp, t_cmd **par);

/**
 ** signal.c
 **/

void		signal_handler(int signum);

/**
 ** find_cmd.c
 **/

void		create_argv(char ***argc, t_que *cmd);
void		free_argv(char ***argc);
void		find_path_cmd(char **div_path, char ***envp, t_que *cmd);

/**
 ** find_red.c
 **/

int			redirect_inp(t_que *red);
int			redirect_add(t_que *red);
int			redirect_app(t_que *red);
int			redirect_rdin(int std_in, t_que *red);

/**
 ** ko_utils.c
 **/

void		do_join(int mode, char **src, char *dst);
char		*ko_delete_ch(const char *str, int d);
int			close_quotes(int x, char *line);
int			ko_putchar(int c);
void		free_split(char **split);
char		*koala_getenv(char *variable, char **envp);
char		*koala_getcwd(void);
char		*get_errorvar(int exit_status, int ret);

/**
 ** termcaps_op.c
 **/

char		delete_tc(t_tty_info *tty_info);
char		reset_line_tc(t_tty_info *tty_info);
int			arrow_functions(t_tty_info *tty_info, char n);

/**
 ** koala_history.c
 **/

t_dlist		*charge_history(void);
void		save_history(t_dlist **list);
void		put_history(t_tty_info *tty_info, char n);
void		exit_tc(void);

/**
 ** exec_builtins.c
 **/

int			exec_builtin(t_dlist *history, char ***argv, char ***envp);
int			koala_exit(t_dlist *history, char **argv);

/**
 ** cd_builtin.c
 **/

int			koala_cd(char **argv, char ***envp);

/**
 ** export_builtin.c
 **/

int			koala_export(char ***envp, char **argv);
void		split_env(const char *string, char **variable, char **value);

/**
 ** export_builtin_utils.c
 **/

int			compare_env_var(char *env, char *new_env);
void		print_export(char **envp);
int			valid_env(char *line);


/**
 ** unset_builtin.c
 **/

void		koala_unset(char ***envp, char **argv);

/**
 ** exit_builtin.c
 **/

int			koala_exit(t_dlist *history, char **argv);

/**
 ** manege_pipe.c
 **/

void		manege_pipe(t_cmd *tmp, int fd[2], pid_t pid);
void		reset_fds(int mode);
pid_t		multi_process_manegment(pid_t **pids);
void		wait_several_processes(pid_t *pids);

#endif
