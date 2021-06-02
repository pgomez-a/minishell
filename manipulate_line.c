/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:18:19 by pgomez-a          #+#    #+#             */
/*   Updated: 2021/06/02 16:35:36 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "koala.h"

static void	free_cmd(t_cmd **par)
{
	while ((*par)->cmd != NULL)
	{
		if ((*par)->err != 1)
		{
			ft_printf("mode: %d -->", (*par)->cmd->op);
			ft_printf(" cmd: **%s**\n", (*par)->cmd->line);
		}
		free(pop_que(&((*par)->cmd)));
	}
	while ((*par)->red != NULL)
	{
		if ((*par)->err != 1)
		{
			ft_printf("mode: %d -->", (*par)->red->op);
			ft_printf(" red: **%s**\n", (*par)->red->line);
		}
		free(pop_que(&((*par)->red)));
	}
}

static void	free_parser(t_cmd **par)
{
	t_cmd	*tmp;

	while (*par != NULL)
	{
		ft_printf("\nNUEVO COMANDO\n");
		free_cmd(par);
		tmp = *par;
		(*par) = (*par)->next;
		free(tmp);
		tmp = NULL;
	}
}

/**
 ** Calls the lexer, the parser and the executor programs
 **/

void	man_command_line(t_que **tail)
{
	t_que	*lex;
	t_cmd	*par;
	char	*line;

	while (*tail)
	{
		line = pop_que(tail);
		lex = NULL;
		par = (t_cmd *)malloc(sizeof(t_cmd));
		call_lexer(line, &lex);
		call_parser(&lex, &par);
		free_parser(&par);
		free(line);
	}
}
