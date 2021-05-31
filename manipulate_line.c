/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:18:19 by pgomez-a          #+#    #+#             */
/*   Updated: 2021/05/31 18:45:40 by pgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "koala.h"

static void	free_cmd(t_cmd **par)
{
	while ((*par)->cmd != NULL)
	{
		if ((*par)->err != 1)
			ft_printf("cmd: %s\n", (*par)->cmd->line);
		free(pop_que(&((*par)->cmd)));
	}
	while ((*par)->inp != NULL)
	{
		if ((*par)->err != 1)
			ft_printf("inp: %s\n", (*par)->inp->line);
		free(pop_que(&((*par)->inp)));
	}
	while ((*par)->out != NULL)
	{
		if ((*par)->err != 1)
		{
			ft_printf("mode: %d -->", (*par)->out->op);
			ft_printf(" out: %s\n", (*par)->out->line);
		}
		free(pop_que(&((*par)->out)));
	}
}

static void	free_parser(t_cmd **par)
{
	t_cmd	*tmp;

	while (*par != NULL)
	{
		ft_printf("NUEVO COMANDO\n");
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
