/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:18:19 by pgomez-a          #+#    #+#             */
/*   Updated: 2021/06/01 10:43:50 by pgomez-a         ###   ########.fr       */
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

static void	free_lexer(t_que **lex)
{
	if (*lex)
	{
		while (*lex)
		{
			ft_printf("%d --> **%s**\n", (*lex)->op, (*lex)->line);
			free(pop_que(lex));
		}
	}
}

/**
 ** Calls the lexer, the parser and the executor programs
 **/

void	man_command_line(char *line)
{
	t_que	*lex;
	//t_cmd	*par;

	if (line)
	{
		lex = NULL;
		//par = (t_cmd *)malloc(sizeof(t_cmd));
		call_lexer(line, &lex);
		free_lexer(&lex);
		//call_parser(&lex, &par);
		//free_parser(&par);
	}
}
