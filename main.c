/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 08:46:43 by pgomez-a          #+#    #+#             */
/*   Updated: 2021/05/26 10:03:53 by pgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static void	check_command_line(char *line, t_que **tail)
{
	char	*tmp;
	int	single;
	int	doble;
	int	x;

	tmp = line;
	single = -1;
	doble = -1;
	x = 0;
	while (tmp[x])
	{
		if (tmp[x] == '\"' && single == -1)
			doble *= -1;
		else if (tmp[x] == '\'' && doble == -1)
			single *= -1;
		else if (tmp[x] == ';' && single == -1 && doble == -1)
		{
			tmp[x] = '\0';
			push_que(tmp, tail);
			tmp = tmp + x + 1;
			x = 0;
		}
		x++;
	}
	if (x > 0)
		push_que(tmp, tail);



	/* Eliminar en el futuro, porque se libera al hacer pop_que */
	while (*tail)
	{
		ft_printf("%s\n", (*tail)->line);
		free((*tail)->line);
		free(*tail);
		(*tail) = (*tail)->next;
	}
}

int	main(void)
{
	t_que	*tail;
	char	buffer[2];
	char	*str;
	char	*tmp;

	buffer[1] = '\0';
	while (1)
	{
		tail = NULL;
		str = ft_strdup("");
		write(1, "koala# ", 7);
		read(1, buffer, 1);
		while (buffer[0] != '\n')
		{
			tmp = str;
			str = ft_strjoin(str, buffer);
			free(tmp);
			read(1, buffer, 1);
		}
		check_command_line(str, &tail);
		//exec_command_line(&tail);
		free(str);
	}
}
