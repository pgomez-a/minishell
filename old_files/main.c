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

#include "minishell.h"

/**
 ** Check if opened quotes have been closed
 **/

static void	check_if_quotes(int single, int doble, char *buffer)
{
	if (buffer[0] == '\n' && single == 1)
		write(1, "quote> ", 7);
	else if (buffer[0] == '\n' && doble == 1)
		write(1, "dquote> ", 8);
}

/**
 ** Reads the command line considering " & ' and stopping when \n is found
 **/

static void	read_command_line(char **str)
{
	char	buffer[2];
	char	*tmp;
	int	single;
	int	doble;

	single = -1;
	doble = -1;
	buffer[1] = '\0';
	write(1, "koala# ", 7);
	read(1, buffer, 1);
	while (buffer[0] != '\n' || single == 1 || doble == 1)
	{
		tmp = *str;
		(*str) = ft_strjoin(*str, buffer);
		free(tmp);
		if (buffer[0] == '\"' && single == -1)
			doble *= -1;
		else if (buffer[0] == '\'' && doble == -1)
			single *= -1;
		check_if_quotes(single, doble, buffer);
		read(1, buffer, 1);
	}
}

/**
 ** Use a queu struct to push lines separated by ; considering " & '
 **/

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
}

int	main(void)
{
	t_que	*tail;
	char	*line;

	while (1)
	{
		tail = NULL;
		line = ft_strdup("");
		read_command_line(&line);
		check_command_line(line, &tail);
		man_command_line(&tail);
		free(line);
	}
}
