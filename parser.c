/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:30:42 by pgomez-a          #+#    #+#             */
/*   Updated: 2021/05/31 18:53:11 by pgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "koala.h"

static void	init_cmd(t_cmd **par)
{
	(*par)->cmd = NULL;
	(*par)->inp = NULL;
	(*par)->out = NULL;
	(*par)->next = NULL;
}

static void	find_pipe(t_cmd **par)
{
	(*par)->next = (t_cmd *)malloc(sizeof(t_cmd));
	(*par) = (*par)->next;
	init_cmd(par);
}

static void	find_inp(char *line, t_que **lex, t_cmd **par)
{
	int	op;

	free(pop_que(lex));
	free(line);
	line = ft_strdup((*lex)->line);
	op = (*lex)->op;
	if (op == 0)
		push_que(0, line, &((*par)->inp));
}

static void	find_out(int mode, char *line, t_que **lex, t_cmd **par)
{
	int	op;

	if (*lex)
	{
		free(pop_que(lex));
		if (*lex)
		{
			free(line);
			line = ft_strdup((*lex)->line);
			op = (*lex)->op;
			if (op == 0)
				push_que(mode, line, &((*par)->out));
			else
				ft_printf("koala: parse error near '%s'\n", line);
		}
		else
			ft_printf("koala: parse error near '\\n'\n");
	}
	else
		ft_printf("koala: parse error near '\\n'\n");
}

static void	check_operator(char *line, t_que **lex, t_cmd **par)
{
	int		verif;

	verif = ft_strncmp("|", line, ft_strlen(line));
	if (verif == 0)
		find_pipe(par);
	verif = ft_strncmp("<", line, ft_strlen(line));
	if (verif == 0)
		find_inp(line, lex, par);
	verif = ft_strncmp(">>\0", line, 3);
	if (verif == 0)
		find_out(2, line, lex, par);
	verif = ft_strncmp(">\0", line, 2);
	if (verif == 0)
		find_out(1, line, lex, par);
}

void	call_parser(t_que **lex, t_cmd **par)
{
	t_cmd	*tmp;
	char	*line;
	int		op;

	tmp = *par;
	init_cmd(&tmp);
	while (*lex)
	{
		line = ft_strdup((*lex)->line);
		op = (*lex)->op;
		if (op == 0)
			push_que(0, line, &(tmp->cmd));
		else
			check_operator(line, lex, &tmp);
		if (*lex)
			free(pop_que(lex));
		free(line);
	}
}
