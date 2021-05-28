/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   koala.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:24:49 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/05/27 11:24:49 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "koala.h"

int		prepare_terminal(void)
{
	struct termios	tty_settings;
	int				tty_fd;

	if (isatty(STDIN_FILENO))
		tty_fd = STDIN_FILENO;
	tcgetattr(tty_fd, &tty_settings);
	tty_settings.c_lflag |= ICANON;
	tty_settings.c_lflag |= ECHO;
	tty_settings.c_lflag |= ISIG; //permite recibir señales
	tty_settings.c_lflag |= ECHOE;

	tcsetattr(tty_fd, TCSANOW, &tty_settings);
	return (tty_fd);
}

void	set_prompt(int tty_fd)
{
	char	*prompt;

	prompt = "koala# ";
	write (tty_fd, prompt, ft_strlen(prompt));
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
	read(tty_fd, buffer, 1);
	while (buffer[0] != '\n' || single == 1 || doble == 1)
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
		read(tty_fd, buffer, 1);
	}
}

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
	int		tty_fd;
	char	*line;
	t_que	*cmds;

	tty_fd = prepare_terminal();
	while (1)
	{
		cmds = 0;
		set_prompt(tty_fd);
		line = ft_strdup("");
		read_command_line(tty_fd, &line);
		check_command_line(line, &cmds);
		man_command_line(&cmds); //recibe cola modificar la line anterior para que devuelva la cola;
		free(line);
	}
	return (0);
}
