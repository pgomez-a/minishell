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
		ft_memcpy(&tty_settings, &original_tty_settings, sizeof(struct termios));
		tty_settings.c_iflag &= ~(IXON);
		tty_settings.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
		tty_settings.c_oflag &= ~(OPOST);
		tcsetattr(tty_fd, TCSANOW, &tty_settings);
	}
	return (tty_fd);
}

void	set_prompt(int tty_fd)
{
	char	*prompt;

	prompt = "koala# ";
	write (tty_fd, prompt, ft_strlen(prompt));
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
			x = -1;
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
