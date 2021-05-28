/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 17:12:25 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/05/28 17:12:25 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "koala.h"

static char	read_fromtty(int tty_fd, char **line)
{
	char	buff;

	(void)line;
	read(tty_fd, &buff, 1);
	if (!ft_isprint(buff))
	{
		if (buff == 3)
			return ('\n');
		//if (buff == 127)
			//return (delete_tc(tty_fd, line));
	}
	write(tty_fd, &buff, 1);
	return (buff);
}

void	read_command_line(int tty_fd, char **line)
{
	char	buffer[2];
	char	*tmp;
	int	single;
	int	doble;

	single = -1;
	doble = -1;
	buffer[1] = '\0';
	buffer[0] = read_fromtty(tty_fd, line);
	while (*buffer && (buffer[0] != '\n' || single == 1 || doble == 1))
	{
		tmp = *line;
		(*line) = ft_strjoin(*line, buffer);
		free(tmp);
		if (buffer[0] == '\"' && single == -1)
			doble *= -1;
		else if (buffer[0] == '\'' && doble == -1)
			single *= -1;
		if (buffer[0] == '\n' && single == 1)
			write(tty_fd, "quote> ", 7);
		else if (buffer[0] == '\n' && doble == 1)
			write(tty_fd, "dquote> ", 8);
		buffer[0] = read_fromtty(tty_fd, line);
	}
}
