/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 10:44:07 by pgomez-a          #+#    #+#             */
/*   Updated: 2021/06/01 10:44:09 by pgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "koala.h"

/**
 ** Push a token if it's valid and create a new one
 **/

void	check_if_push(int mode, int *x, char **out, t_que **lex)
{
	if (*(*out) != '\0')
	{
		push_que(x[1], *out, lex);
		x[2] = 0;
	}
	free(*out);
	if (mode == 1)
	{
		(*out) = ft_strdup("");
		x[1] = 0;
	}
	else if (mode == 0)
		(*out) = NULL;
}

/**
 ** Check if a char should be joined to the token string
 **/

void	check_if_join(int *x, int back, char *line, char **out)
{
	char	*str;
	int		ct;

	str = ft_charstr(line[x[0]]);
	if (line[x[0]] != '\n' || (line[x[0]] == '\n' && back == 0))
		do_join(out, str);
	if (line[x[0]] == '$' && back == 0 && line[x[0] + 1])
	{
		ct = 1;
		ct = ct << x[2];
		x[1] |= ct;
	}
	if (line[x[0]] == '$')
		x[2] += 1;
	free(str);
}

/**
 ** Tokenize when valid sin quote is found with no special elements
 **/

int	check_sin_quote(int *x, char *line, char **out, t_que **lex)
{
	int	back;

	back = look_back_slash(line, line + x[0] - 1);
	if (back == 0)
	{
		check_if_push(1, x, out, lex);
		x[0]++;
		while (line[x[0]] != '\'')
		{
			check_if_join(x, back, line, out);
			x[0] += 1;
		}
		x[1] = 0;
		check_if_push(1, x, out, lex);
		return (x[0]);
	}
	check_if_join(x, back, line, out);
	return (x[0]);
}

/**
 ** Tokenize when valid dob quote is found and count number of valid $
 **/

static int	bool_dob_quote(int *x, char *line, char **out, t_que **lex)
{
	int	op;
	int	var;
	int	back;

	op = 0;
	var = 0;
	back = look_back_slash(line, line + x[0] - 1);
	while ((line[x[0]] && line[x[0]] != '\"')
		|| (line[x[0]] == '\"' && back != 0))
	{
		if ((line[x[0]] == '\\' && line[x[0] + 1] != '\n'
				&& line[x[0] + 1] != '$' && line[x[0] + 1] != '\"'
				&& back == 0) || line[x[0]] != '\\')
			check_if_join(x, back, line, out);
		if (line[x[0]] == '$' && back == 0 && line[x[0] + 1])
			var |= (1 << op);
		if (line[x[0]] == '$')
			op++;
		x[0]++;
		back = look_back_slash(line, line + x[0] - 1);
	}
	return (var);
}

int	check_dob_quote(int *x, char *line, char **out, t_que **lex)
{
	int	op;
	int	back;

	op = 0;
	back = look_back_slash(line, line + x[0] - 1);
	if (back == 0)
	{
		check_if_push(1, x, out, lex);
		x[0]++;
		x[1] = bool_dob_quote(x, line, out, lex);
		check_if_push(1, x, out, lex);
		return (x[0]);
	}
	check_if_join(x, back, line, out);
	return (x[0]);
}
