/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 18:22:21 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/05/28 18:22:21 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "koala.h"

int	move_cursor(t_tty_info *tty_info, char n)
{
	if (n == 0)
	{
		read(0, &n, 1);
		read(0, &n, 1);
	}
	if (n == 'C' && tty_info->xcursor != ft_strlen(tty_info->string))
	{
		tputs(cursor_right, 1, ko_putchar);
		tty_info->xcursor++;
		return (1);
	}
	if (n == 'D' && tty_info->xcursor != 0)
	{
		tputs(cursor_left, 1, ko_putchar);
		tty_info->xcursor--;
		return (1);
	}
	return (0);
}

char	reset_line_tc(t_tty_info *tty_info)
{
	char	*tmp;

	tmp = tty_info->string;
	tty_info->string = ft_strdup("");
	free(tmp);
	tty_info->xcursor = 0;
	return ('\n');
}

char	delete_tc(t_tty_info *tty_info)
{
	char	*tmp;

	if (!*(tty_info->string))
		return (0);
	if (move_cursor(tty_info, 'D'))
	{
		tmp = tty_info->string;
		tty_info->string = ft_substr(tmp, 0, tty_info->xcursor - 1);
		tty_info->string = ko_delete_ch(tmp, tty_info->xcursor);
		free(tmp);
		tputs(delete_character, 1, ko_putchar);
	}
	return (0);
}
