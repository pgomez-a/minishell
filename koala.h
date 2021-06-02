/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   koala.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:24:53 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/05/31 17:19:43 by pgomez-a         ###   ########.fr       */
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
# include "libft/libft.h"
# include "./queue/queue.h"

typedef struct s_cmd
{
	t_que			*cmd;
	t_que			*red;
	int				err;
	struct s_cmd	*next;
}	t_cmd;

typedef struct	s_tty_info
{
	int				tty_fd;
	unsigned int	xcursor;
	char			*string;
	struct termios	tty_settings;
	struct termios	original_tty_settings;
}	t_tty_info;

/* set the the configuration for the tty */
t_tty_info	*prepare_terminal(t_tty_info *tty_info, int tty_mode);

/* read from the tty */
void	read_command_line(t_tty_info *tty_info);

/* check_prompt.c */
void	check_command_line(char *line, t_que **tail);

/* manipulate_line.c */
void	man_command_line(t_que **tail);

/* lexer.c */
void	call_lexer(char *line, t_que **lex);

/* check_lexer.c */
void	check_if_push(int mode, int *x, char **out, t_que **lex);
void	check_if_join(int *x, int back, char *line, char **out);
int		check_sin_quote(int *x, char *line, char **out, t_que **lex);
int		check_dob_quote(int *x, char *line, char **out, t_que **lex);

/* parser.c */
void	call_parser(t_que **lex, t_cmd **par);

/* check_parser.c */
void	init_cmd(t_cmd **par);
void	find_pipe(t_que **lex, t_cmd **par);
void	find_dollar(char *line, t_que **lex, t_cmd **par);
int		find_red(int mode, char *line, t_que **lex, t_cmd **par);

/* ko_utils.c */
int		look_back_slash(char *beg, char *end);
void	do_join(char **src, char *dst);
void	set_prompt(t_tty_info *tty_info);
int		ko_putchar(int c);
char	*ko_delete_ch(const char *str, int d);

/* termcaps output modicator functions */
char	delete_tc(t_tty_info *tty_info);
char	reset_line_tc(t_tty_info *tty_info);
int		move_cursor(t_tty_info *tty_info, char n);

#endif
