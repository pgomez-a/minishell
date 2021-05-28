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

void	read_line(int tty_fd, char **line)
{
	char	buffer[2];
	char	*tmp;
	int	single;
	int	doble;

	*line = ft_strdup("");
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


int	main(void)
{
	int		tty_fd;
	char	*line;

	tty_fd = prepare_terminal();
	while (1)
	{
		set_prompt(tty_fd);
		read_line(tty_fd, &line);
		man_command_line() //recibe cola modificar la line anterior para que devuelva la cola;
	}
	return (0);
}
