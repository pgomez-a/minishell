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
