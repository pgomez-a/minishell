/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 08:42:24 by pgomez-a          #+#    #+#             */
/*   Updated: 2021/07/05 13:51:16 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

void	push_que(int op, char *line, t_que **que)
{
	t_que	*tmp;

	if (*que)
	{
		tmp = *que;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_que *)malloc(sizeof(t_que));
		if (line)
			tmp->next->line = ft_strdup(line);
		tmp->next->op = op;
		tmp->next->next = NULL;
	}
	else
	{
		(*que) = (t_que *)malloc(sizeof(t_que));
		if (line)
			(*que)->line = ft_strdup(line);
		(*que)->op = op;
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
		if (tmp->line)
		{
			out = ft_strdup(tmp->line);
			free(tmp->line);
		}
		free(tmp);
		tmp = NULL;
	}
	return (out);
}
