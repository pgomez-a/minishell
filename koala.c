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

static int		prepare_terminal(int tty_fd, int reset)
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
		tgetent(0, getenv("TERM"));
		ft_memcpy(&tty_settings, &original_tty_settings, sizeof(struct termios));
		tty_settings.c_iflag &= ~(IXON);
		tty_settings.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
		tty_settings.c_oflag &= ~(OPOST);
		tcsetattr(tty_fd, TCSANOW, &tty_settings);
	}
	return (tty_fd);
}

int	main(void)
{
	t_que	*cmds;
	char	*line;
	int		tty_fd;

	tty_fd = -1;
	tty_fd = prepare_terminal(tty_fd, 0);
	while (1)
	{
		cmds = 0;
		set_prompt(tty_fd);
		line = ft_strdup("");
		read_command_line(tty_fd, &line);
		if (*line == 'q') // salida temporal para probar hasta tener el builtin de exit
		{
			free(line);
			prepare_terminal(tty_fd, 1);
			exit(-1);
		}
		check_command_line(line, &cmds);
		man_command_line(&cmds); // recibe cola modificar la line anterior para que devuelva la cola;
		free(line);
	}
	return (0);
}
