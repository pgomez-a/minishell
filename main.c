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

static void	check_command_line(char *line)
{
	t_que	*tail;
	char	**div;
	char	*str;
	int		x;

	div = ft_split(line, ';');
	x = 0;
	while (div[x])
	{
		str = ft_strtrim(div[x], " ");
		push_que(str, &tail);
		free(str);
		free(div[x]);
		x++;
	}
	free(div);



	while (tail)
	{
		ft_printf("%s\n", tail->line);
		free(tail->line);
		free(tail);
		tail = tail->next;
	}
}

int	main(void)
{
	char	buffer[2];
	char	*str;
	char	*tmp;

	buffer[1] = '\0';
	while (1)
	{
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
		check_command_line(str);
		free(str);
	}
}
