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

void	read_command_line(t_tty_info *tty_info)
{
	char	buffer[2];
	int	single;
	int	doble;
	int	back;

	single = -1;
	doble = -1;
	buffer[1] = '\0';
	buffer[0] = read_fromtty(tty_info);
	back = 0;
	while (buffer[0] != '\n' || single == 1 || doble == 1)
	{
		do_join(&tty_info->string, buffer);
		if (buffer[0] == '\"' && single == -1 && (back % 2 == 0))
			doble *= -1;
		else if (buffer[0] == '\'' && doble == -1)
		{
			if ((back % 2 == 0 && single == -1) || single == 1)
				single *= -1;
		}
		if (buffer[0] == '\n' && single == 1)
			write(tty_info->tty_fd, "quote> ", 7);
		else if (buffer[0] == '\n' && doble == 1)
			write(tty_info->tty_fd, "dquote> ", 8);
		back = get_num_back_slash(tty_info->string, (tty_info->string) + ft_strlen(tty_info->string) - 1);
		buffer[0] = read_fromtty(tty_info);
	}
}

/**
 ** Put each line separated by ; in a queue
 **/

void	check_command_line(char *line, t_que **tail)
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
