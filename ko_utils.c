/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ko_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:18:36 by pgomez-a          #+#    #+#             */
/*   Updated: 2021/05/31 16:18:38 by pgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "koala.h"

/**
 ** Join the two given stings and avoid memory leaks
 **/

void	do_join(int mode, char **src, char *dst)
{
	char	*tmp;

	tmp = *src;
	(*src) = ft_strjoin(*src, dst);
	free(tmp);
	if (mode == 1)
		free(dst);
}

/**
 ** Write koala prompt
 **/

void	set_prompt(int tty_fd)
{
	char	*prompt;

	prompt = "koala# ";
	write(tty_fd, prompt, ft_strlen(prompt));
}

/**
 ** Check if there are close quotes or not
 **/

int	close_quotes(char quot, char *line)
{
	int	count;

	count = 1;
	while (line[count])
	{
		if (line[count] == quot)
			return (1);
		count++;
	}
	return (0);
}
