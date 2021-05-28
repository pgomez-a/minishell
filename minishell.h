/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 08:46:50 by pgomez-a          #+#    #+#             */
/*   Updated: 2021/05/26 08:46:52 by pgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./queue/queue.h"
# include <stdio.h>

typedef struct	s_cmd
{
	char	*builtin;
	char	**flags;
	char	**args;
	//void	*next;
	//char	link;
}	t_cmd;

/* manipulate_line.c */
void	man_command_line(t_que **tail);

/* lexer.c */
void	call_lexer(char *line, t_que **lex);

#endif
