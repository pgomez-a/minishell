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

static t_tty_info	*prepare_terminal(t_tty_info *tty_info, int reset)
{
	static struct termios	original_tty_settings;
	struct termios			tty_settings;

	if (reset)
		tcsetattr(tty_info->tty_fd, TCSANOW, &original_tty_settings);
	else
	{
		tty_info = ft_calloc(1, sizeof(t_tty_info));
		tty_info->tty_fd = -1;
		tcgetattr(STDIN_FILENO, &original_tty_settings);
		if (isatty(STDIN_FILENO))
			tty_info->tty_fd = STDIN_FILENO;
		if (tty_info->tty_fd == -1)
			exit(-1);
		tgetent(0, getenv("TERM"));
		ft_memcpy(&tty_settings, &original_tty_settings, sizeof(struct termios));
		tty_settings.c_iflag &= ~(IXON);
		tty_settings.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
		tty_settings.c_oflag &= ~(OPOST);
		tcsetattr(tty_info->tty_fd, TCSANOW, &tty_settings);
	}
	return (tty_info);
}

int	main(void)
{
	t_que			*cmds;
	t_tty_info		*tty_info;

	tty_info = 0;
	tty_info = prepare_terminal(tty_info, 0); //alllocates tty_info remenber to free
	//nline = tgetnum();
	while (1)
	{
		cmds = 0;
		set_prompt(tty_info);
		tty_info->string = ft_strdup("");
		read_command_line(tty_info);
		tputs(carriage_return, 1, ko_putchar);
		if (*(tty_info->string) == 'q') // salida temporal para probar hasta tener el builtin de exit
		{
			free(tty_info->string);
			prepare_terminal(tty_info, 1);
			exit(-1);
		}
		check_command_line(tty_info->string, &cmds);
		man_command_line(&cmds);
		free(tty_info->string);
	}
	return (0);
}
