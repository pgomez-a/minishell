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

static int	prepare_terminal(int tty_fd, int reset)
{
	static struct termios	original_tty_settings;
	struct termios			tty_settings;

	if (reset)
		tcsetattr(tty_fd, TCSANOW, &original_tty_settings);
	else
	{
		tcgetattr(STDIN_FILENO, &original_tty_settings);
		if (isatty(STDIN_FILENO))
			tty_fd = STDIN_FILENO;
		if (tty_fd == -1)
			exit(-1);
		ft_memcpy(&tty_settings, &original_tty_settings, sizeof(struct termios));
		//ft_bzero(&tty_settings, sizeof(struct termios));
		tty_settings.c_lflag |= ICANON;
		tty_settings.c_lflag |= ECHO;
		tty_settings.c_lflag |= ISIG; //permite recibir señales
		tty_settings.c_lflag |= ECHOE;
		tcsetattr(tty_fd, TCSANOW, &tty_settings);
	}
		return (tty_fd);
}

int	main(void)
{
	char	*line;
	int		tty_fd;

	tty_fd = -1;
	tty_fd = prepare_terminal(tty_fd, 0);
	while (1)
	{
		set_prompt(tty_fd);
		line = ft_strdup("");
		read_command_line(tty_fd, &line);
		if (*line == 'q') // esto borrar
		{
			free(line);
			prepare_terminal(tty_fd, 1);
			exit(-1);
		}
		man_command_line(line); // recibe cola modificar la line anterior para que devuelva la cola;
		free(line);
	}
	return (0);
}
