/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:18:30 by pgomez-a          #+#    #+#             */
/*   Updated: 2021/06/01 09:19:26 by pgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "koala.h"

/**
 ** Read user input from prompt
 **/

static int	set_quot_prompt(int tty_fd, int sin, int dob, char *buff)
{
	if (sin == dob && sin == -2)
	{
		write(tty_fd, "> ", 2);
		return (1);
	}
	if (buff[0] == '\n' && sin == 1)
		write(tty_fd, "quote> ", 7);
	else if (buff[0] == '\n' && dob == 1)
		write(tty_fd, "dquote> ", 8);
	return (0);
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

void	read_command_line(int tty_fd, char **line)
{
	char	buff[2];
	int		sin;
	int		dob;
	int		back;
	int		slash;

	sin = -1;
	dob = -1;
	buff[1] = '\0';
	read(tty_fd, buff, 1);
	back = 0;
	slash = 0;
	while (buff[0] != '\n' || sin == 1 || dob == 1 || slash == 1)
	{
		slash = 0;
		do_join(line, buff);
		look_quotes(back, buff, &sin, &dob);
		if (buff[0] == '\\' && back == 0 && sin == -1 && dob == -1)
			slash = set_quot_prompt(tty_fd, -2, -2, buff);
		else
			slash = set_quot_prompt(tty_fd, sin, dob, buff);
		back = look_back_slash(*line, (*line) + ft_strlen(*line) - 1);
		read(tty_fd, buff, 1);
	}
}

/**
 ** Put each line separated by ; in a queue
 **/

static void	loop_sinquote(int *num, char *beg, char *end)
{
	if (!(end > beg && *(end - 1) == '\\' && (*num) == -1))
		(*num) *= -1;
}

static void	loop_semicolon(int back, char **beg, char **end, t_que **tail)
{
	(**end) = '\0';
	if (back != 0)
		*(*end - 1) = '\0';
	if (**beg)
		push_que(0, *beg, tail);
	(*beg) = (*end) + 1;
}

void	check_command_line(char *line, t_que **tail)
{
	char	*beg;
	char	*end;
	int		sin;
	int		dob;
	int		back;

	beg = line;
	end = line;
	sin = -1;
	dob = -1;
	while (*end)
	{
		back = look_back_slash(beg, end - 1);
		if ((*end) == '\"' && sin == -1 && back == 0)
			dob *= -1;
		else if ((*end) == '\'' && dob == -1 && back == 0)
			loop_sinquote(&sin, beg, end);
		else if ((*end) == ';' && back == 0 && dob == -1 && sin == -1)
			loop_semicolon(back, &beg, &end, tail);
		end++;
	}
	if (*beg)
		push_que(0, beg, tail);
}
