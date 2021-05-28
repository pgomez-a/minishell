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

/* manipulate_line.c */
void	man_command_line(t_que **tail);

/* lexer.c */
void	call_lexer(char *line, t_que **lex);

/* ft_utils.c */
void	do_join(char **src, char *dst);
void	set_prompt(int tty_fd);

#endif
