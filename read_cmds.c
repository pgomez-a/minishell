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

static char	read_fromtty(t_tty_info *tty_info)
{
	char	buff;

	read(tty_info->tty_fd, &buff, 1);
	if (!ft_isprint(buff) && buff != '\n')
	{
		if (buff == 3)
			return (reset_line_tc(tty_info));
		if (buff == 127)
			return (delete_tc(tty_info));
		if (buff == '\033')
			move_cursor(tty_info, 0);
		//printf("Valor del caracter en buff: %i\n", buff);
		return (0);
	}
	write(tty_info->tty_fd, &buff, 1);
	tty_info->xcursor++;
	return (buff);
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

static void	set_quot_prompt(int tty_fd, int sin, int dob, char *buff)
{
	if (buff[0] == '\n' && sin == 1)
		write(tty_fd, "quote> ", 7);
	else if (buff[0] == '\n' && dob == 1)
		write(tty_fd, "dquote> ", 8);
}

static void	look_quotes(int back, char *buff, int *sin, int *dob)
{
	if (buff[0] == '\"' && (*sin) == -1 && back == 0)
		(*dob) *= -1;
	else if (buff[0] == '\'' && (*dob) == -1)
	{
		if ((back == 0 && (*sin) == -1) || (*sin) == 1)
			(*sin) *= -1;
	}
}

void	read_command_line(t_tty_info *tty_info)
{
	char	buff[2];
	int		sin;
	int		dob;
	int		back;

	sin = -1;
	dob = -1;
	buff[1] = '\0';
	buff[0] = read_fromtty(tty_info);
	back = 0;
	while (buff[0] != '\n' || sin == 1 || dob == 1)
	{
		do_join(&tty_info->string, buff);
		look_quotes(back, buff, &sin, &dob);
		set_quot_prompt(tty_info->tty_fd, sin, dob, buff);
		back = look_back_slash(tty_info->string, (tty_info->string) + ft_strlen(tty_info->string) - 1);
		buff[0] = read_fromtty(tty_info);
	}
}
