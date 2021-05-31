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
	(*par)->err = 0;
}

static void	find_pipe(t_que **lex, t_cmd **par)
{
	if ((*lex)->next)
	{
		(*par)->next = (t_cmd *)malloc(sizeof(t_cmd));
		(*par) = (*par)->next;
		init_cmd(par);
	}
	else
		ft_printf("koala: parse error near '|'\n");
}

static int	find_inp(char *line, t_que **lex, t_cmd **par)
{
	int	op;

	(*par)->err = 1;
	if (*lex)
	{
		free(pop_que(lex));
		if (*lex)
		{
			free(line);
			line = ft_strdup((*lex)->line);
			op = (*lex)->op;
			if (op == 0)
			{
				push_que(0, line, &((*par)->inp));
				(*par)->err = 0;
				return (0);
			}
			ft_printf("koala: parse error near '%s'\n", line);
			return (1);
		}
		ft_printf("koala: parse error near '\\n'\n");
		return (1);
	}
	ft_printf("koala: parse error near '\\n'\n");
	return (1);
}

static int	find_out(int mode, char *line, t_que **lex, t_cmd **par)
{
	int	op;

	(*par)->err = 1;
	if (*lex)
	{
		free(pop_que(lex));
		if (*lex)
		{
			free(line);
			line = ft_strdup((*lex)->line);
			op = (*lex)->op;
			if (op == 0)
			{
				push_que(mode, line, &((*par)->out));
				(*par)->err = 0;
				return (0);
			}
			ft_printf("koala: parse error near '%s'\n", line);
			return (1);
		}
		ft_printf("koala: parse error near '\\n'\n");
		return (1);
	}
	ft_printf("koala: parse error near '\\n'\n");
	return (1);
}

static int	check_operator(char *line, t_que **lex, t_cmd **par)
{
	int		verif;
	int		out;

	out = 0;
	verif = ft_strncmp("|", line, ft_strlen(line));
	if (verif == 0)
		find_pipe(lex, par);
	verif = ft_strncmp("<", line, ft_strlen(line));
	if (verif == 0 && (*par)->err != 1)
		out = find_inp(line, lex, par);
	verif = ft_strncmp(">>\0", line, 3);
	if (verif == 0 && (*par)->err != 1)
		out = find_out(2, line, lex, par);
	verif = ft_strncmp(">\0", line, 2);
	if (verif == 0 && (*par)->err != 1)
		out = find_out(1, line, lex, par);
	return (out);
}

void	call_parser(t_que **lex, t_cmd **par)
{
	t_cmd	*tmp;
	char	*line;
	int		err;
	int		op;

	tmp = *par;
	init_cmd(&tmp);
	if (*(*lex)->line != '|' || (*(*lex)->line == '|' && (*lex)->op != 1))
	{
		while (*lex)
		{
			line = ft_strdup((*lex)->line);
			op = (*lex)->op;
			if (op == 0)
				push_que(0, line, &(tmp->cmd));
			else
				err = check_operator(line, lex, &tmp);
			if (*lex)
				free(pop_que(lex));
			free(line);
		}
	}
	else
	{
		ft_printf("koala: parse error near '|'\n");
		while (*lex)
		{
			tmp->cmd = *lex;
			(*lex) = (*lex)->next;
			free(pop_que(&(tmp->cmd)));
		}
		(*par)->err = 1;
	}
}
