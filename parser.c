/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:30:42 by pgomez-a          #+#    #+#             */
/*   Updated: 2021/06/01 10:43:39 by pgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "koala.h"

static int	check_operator(int err, char *line, t_que **lex, t_cmd **par)
{
	int	pipe;
	int	redAdd;
	int	redAtt;
	int	redInp;
	int	out;

	out = 0;
	pipe = ft_strncmp("|", line, ft_strlen(line));
	redInp = ft_strncmp("<", line, ft_strlen(line));
	redAtt = ft_strncmp(">>\0", line, 3);
	redAdd = ft_strncmp(">\0", line, 2);
	if (err == 0)
	{
		if (pipe == 0)
			find_pipe(lex, par);
		else if (redInp == 0)
			out = find_red(1, line, lex, par);
		else if (redAtt == 0)
			out = find_red(3, line, lex, par);
		else if (redAdd == 0)
			out = find_red(2, line, lex, par);
		else
			find_dollar(line, lex, par);
	}
	return (out);
}

static void	bool_if_line(t_que **lex, t_cmd **tmp)
{
	char	*line;
	int		err;
	int		op;

	err = 0;
	while (*lex)
	{
		err = 0;
		line = ft_strdup((*lex)->line);
		op = (*lex)->op;
		if (op == 0)
			push_que(0, line, &((*tmp)->cmd));
		else
			err = check_operator(err, line, lex, tmp);
		if (*lex)
			free(pop_que(lex));
		free(line);
	}
}

static void	bool_not_line(t_que **lex, t_cmd **tmp, t_cmd **par)
{
	ft_printf("koala: parse error near '|'\n");
	while (*lex)
	{
		(*tmp)->cmd = *lex;
		(*lex) = (*lex)->next;
		free(pop_que(&((*tmp)->cmd)));
	}
	(*par)->err = 1;
}

void	call_parser(t_que **lex, t_cmd **par)
{
	t_cmd	*tmp;

	tmp = *par;
	init_cmd(&tmp);
	if ((*lex))
	{
		if ((*(*lex)->line != '|') || (*(*lex)->line == '|' && (*lex)->op != 1))
			bool_if_line(lex, &tmp);
		else
			bool_not_line(lex, &tmp, par);
	}
}
