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
		//ft_bzero(&tty_settings, sizeof(struct termios));
		tty_settings.c_lflag |= ICANON;
		tty_settings.c_lflag |= ECHO;
		tty_settings.c_lflag |= ISIG; //permite recibir señales
		tty_settings.c_lflag |= ECHOE;
		tcsetattr(tty_fd, TCSANOW, &tty_settings);
	}
		return (tty_fd);
}

static int	get_num_back_slash(char *beg, char *end)
{
	char	*tmp;
	int	count;

	tmp = end;
	count = 0;
	while (tmp >= beg)
	{
		if ((*tmp) != '\\')
			return (count);
		count++;
		tmp--;
	}
	return (count);
}

/**
 ** Read user input from prompt
 **/

static void	read_command_line(int tty_fd, char **line)
{
	char	buffer[2];
	int	single;
	int	doble;
	int	back;

	single = -1;
	doble = -1;
	buffer[1] = '\0';
	read(tty_fd, buffer, 1);
	back = 0;
	while (buffer[0] != '\n' || single == 1 || doble == 1)
	{
		do_join(line, buffer);
		if (buffer[0] == '\"' && single == -1 && (back % 2 == 0))
			doble *= -1;
		else if (buffer[0] == '\'' && doble == -1)
		{
			if ((back % 2 == 0 && single == -1) || single == 1)
				single *= -1;
		}
		if (buffer[0] == '\n' && single == 1)
			write(tty_fd, "quote> ", 7);
		else if (buffer[0] == '\n' && doble == 1)
			write(tty_fd, "dquote> ", 8);
		back = get_num_back_slash(*line, (*line) + ft_strlen(*line) - 1);
		read(tty_fd, buffer, 1);
	}
}

/**
 ** Put each line separated by ; in a queue
 **/

static void	check_command_line(char *line, t_que **tail)
{
	char	*beg;
	char	*end;
	int	single;
	int	doble;
	int	back;

	beg = line;
	end = line;
	single = -1;
	doble = -1;
	while (*end)
	{
		back = get_num_back_slash(beg, end - 1);
		if ((*end) == '\"' && single == -1 && back % 2 == 0)
			doble *= -1;
		else if ((*end) == '\'' && doble == -1 && back % 2 == 0)
		{
			if (!(end > beg && *(end - 1) == '\\' && single == -1))
				single *= -1;
		}
		else if ((*end) == ';' && back % 2 == 0 && doble == -1 && single == -1)
		{
			(*end) = '\0';
			if (back % 2 != 0)
				*(end - 1) = '\0';
			if (*beg)
				push_que(beg, tail);
			beg = end + 1;
		}
		end++;
	}
	if (*beg)
		push_que(beg, tail);
}

int	main(void)
{
	t_que	*cmds;
	char	*line;
	int	tty_fd;

	tty_fd = -1;
	tty_fd = prepare_terminal(tty_fd, 0);
	while (1)
	{
		cmds = 0;
		set_prompt(tty_fd);
		line = ft_strdup("");
		read_command_line(tty_fd, &line);
		if (*line == 'q') // esto borrar
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
