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

#ifndef PROMPT_H
# define PROMPT_H

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

/* exec_command.c */
void	exec_command_line(t_que **tail);

/* ft_utils */
void	clear_cmand_struct(t_cmd *elem);

#endif
