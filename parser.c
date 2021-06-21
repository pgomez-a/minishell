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

/**
 ** Find the operator used to add to command table
 **

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

**
 ** Called if no error ocurred with pipes
 **/

static int	check_pipe(char *line, t_que **lex, t_cmd **tmp)
{
	int	pipe;

	pipe = ft_strncmp("|\0", line, 2);
	if (pipe == 0)
	{
		if ((*lex)->next)
		{
			(*tmp)->next = (t_cmd *)malloc(sizeof(t_cmd));
			(*tmp) = (*tmp)->next;
			init_cmd(tmp);
			return (1);
		}
		(*tmp)->err = 1;
		ft_printf("koala: parse error near '|'\n");
		return (-1);
	}
	return (0);
}

static void	bool_if_line(t_que **lex, t_cmd **tmp)
{
	char	*line;
	int	mode;
	int	button;

	while (*lex && (*tmp)->err == 0)
	{
		button = 0;
		mode = (*lex)->op;
		line = ft_strdup((*lex)->line);
		/*if (mode != 1)
			button = check_red(line, lex, par);
		*/
		if (mode == 0 && button == 0)
			button = check_pipe(line, lex, tmp);
		if (button == 0)
			push_que(0, line, &((*tmp)->cmd));
		if (*lex)
			free(pop_que(lex));
		free(line);
	}
}

/**
 ** Called if there is nothing after pip |
 **/

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

/**
 ** Parse tokens passed by lexer
 **/

void	call_parser(t_que **lex, t_cmd **par)
{
	t_cmd	*tmp;

	tmp = *par;
	init_cmd(&tmp);
	if ((*lex))
	{
		if ((*(*lex)->line == '|' && (*lex)->op != 1))
			bool_not_line(lex, &tmp, par);
		else
			bool_if_line(lex, &tmp);
	}
}
