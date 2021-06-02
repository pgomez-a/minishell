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

int	arrow_functions(t_tty_info *tty_info, char n)
{
	if (n == 'C' && tty_info->xcursor != ft_strlen(tty_info->string))
	{
		tputs(cursor_right, 1, ko_putchar);
		tty_info->xcursor++;
		return (1);
	}
	else if (n == 'D' && tty_info->xcursor != 0)
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
	if (arrow_functions(tty_info, 'D'))
	{
		tmp = tty_info->string;
		tty_info->string = ko_delete_ch(tmp, tty_info->xcursor);
		free(tmp);
		tputs(delete_character, 1, ko_putchar);
	}
	return (0);
}
