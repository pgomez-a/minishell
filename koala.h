/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   koala.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:24:53 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/05/27 11:24:53 by mmunoz-f         ###   ########.fr       */
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

typedef struct	s_cmd
{
	char	*builtin;
	t_que	*flags;
	t_que	*args;
	//void	*next;
	//char	link;
}	t_cmd;

typedef struct	s_tty_info
{
	int				tty_fd;
	unsigned int	xcursor;
	char			*string;
}	t_tty_info;

/* read from the tty */
void	read_command_line(t_tty_info *tty_info);

/* divides lines by ';' */
void	check_command_line(char *line, t_que **tail);

/* manipulate_line.c */
void	man_command_line(t_que **tail);

/* lexer.c */
void	call_lexer(char *line, t_que **lex);

/* ft_utils.c */
void	do_join(char **src, char *dst);
void	set_prompt(t_tty_info *tty_info);
int		ko_putchar(int c);
char	*ko_delete_ch(const char *str, int d);

/* termcaps output modicator functions */
char	delete_tc(t_tty_info *tty_info);
char	reset_line_tc(t_tty_info *tty_info);
int		move_cursor(t_tty_info *tty_info, char n);

#endif
