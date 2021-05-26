/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 08:42:24 by pgomez-a          #+#    #+#             */
/*   Updated: 2021/05/26 08:59:00 by pgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

void	push_que(char *line, t_que **que)
{
	t_que	*tmp;

	if (*que)
	{
		tmp = *que;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_que *)malloc(sizeof(t_que));
		tmp->next->line = ft_strtrim(line, " ");
		tmp->next->next = NULL;
	}
	else
	{
		(*que) = (t_que *)malloc(sizeof(t_que));
		(*que)->line = ft_strtrim(line, " ");
		(*que)->next = NULL;
	}
}

char	*pop_que(t_que **que)
{
	t_que	*tmp;
	char	*out;

	out = NULL;
	if (*que)
	{
		tmp = *que;
		(*que) = (*que)->next;
		out = ft_strdup(tmp->line);
		free(tmp->line);
		free(tmp);
		tmp = NULL;
	}
	return (out);
	
}
