/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:18:05 by pgomez-a          #+#    #+#             */
/*   Updated: 2021/05/31 16:22:25 by pgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "koala.h"

static int	check_redirections(int *x, char *line, char **out, t_que **lex)
{
	int	back;

	back = look_back_slash(line, line + x[0] - 1);
	if (back == 0)
	{
		check_if_push(1, x, out, lex);
		check_if_join(x, back, line, out);
		if (line[x[0]] == '>' && line[x[0] + 1] == '>')
		{
			check_if_join(x, back, line, out);
			x[0] += 1;
		}
		x[1] = 1;
		check_if_push(1, x, out, lex);
		return (x[0]);
	}
	check_if_join(x, back, line, out);
	return (x[0]);
}

void	call_lexer(char *line, t_que **lex)
{
	char	*out;
	int		back;
	int		x[2];

	x[0] = 0;
	x[1] = 0;
	back = 0;
	out = ft_strdup("");
	while (line[x[0]])
	{
		back = look_back_slash(line, line + x[0] - 1);
		if (line[x[0]] == '\'')
			x[0] = check_sin_quote(x, line, &out, lex);
		else if (line[x[0]] == '\"')
			x[0] = check_dob_quote(x, line, &out, lex);
		else if (line[x[0]] == '<' || line[x[0]] == '>' || line[x[0]] == '|')
			x[0] = check_redirections(x, line, &out, lex);
		else if (line[x[0]] == ' ' && back == 0)
			check_if_push(1, x, &out, lex);
		else if (line[x[0]] != '\\' || (line[x[0]] == '\\' && back != 0))
			check_if_join(x, back, line, &out);
		x[0]++;
	}
	check_if_push(0, x, &out, lex);
}
