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

char	reset_line_tc(char **line)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strdup("");
	free(tmp);
	return ('\n');
}

char	delete_tc(char **line)
{
	char	*tmp;

	if (!*line)
		return (0);
	tmp = *line;
	*line = ft_substr(*line, 0, ft_strlen(*line) - 1);
	free(tmp);
	tputs(cursor_left, 1, ko_putchar);
	tputs(delete_character, 1, ko_putchar);
	return (0);
}
