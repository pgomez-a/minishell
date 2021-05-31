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
# include <termios.h>
# include <stdlib.h>
# include "libft/libft.h"
# include "./queue/queue.h"

typedef struct s_cmd
{
	t_que			*cmd;
	t_que			*inp;
	t_que			*out;
	int				err;
	struct s_cmd	*next;
}	t_cmd;

/* read_check.c */
void	read_command_line(int tty_fd, char **line);
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
int		check_redirections(int *x, char *line, char **out, t_que **lex);

/* parser.c */
void	call_parser(t_que **lex, t_cmd **par);

/* ko_utils.c */
int		look_back_slash(char *beg, char *end);
void	do_join(char **src, char *dst);
void	set_prompt(int tty_fd);

#endif
