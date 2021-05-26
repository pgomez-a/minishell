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

typedef struct s_cmd {
	char	*tot;
	char	*cmand;
	char	*param;
	char	*argum;
	int	error;
}	t_cmd;

/* get_command.c */
int	set_command(char *str, t_cmd *elem);

/* ft_utils */
void	clear_cmand_struct(t_cmd *elem);

#endif
