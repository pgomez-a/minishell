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

/**
 ** Create token of closed quotes
 **/

static int	add_to_quote(char quot, char **tok, char *line, t_que **lex)
{
	int	count;

	if ((**tok) != '\0')
		push_que(0, *tok, lex);
	free(*tok);
	(*tok) = ft_strdup("\0");
	count = 1;
	while (line[count])
	{
		if (line[count] == quot)
		{
			if (quot == '\'')
				push_que(1, *tok, lex);
			else if (quot == '\"')
				push_que(2, *tok, lex);
			free(*tok);
			(*tok) = ft_strdup("\0");
			return (count + 1);
		}
		do_join(1, tok, ft_charstr(line[count]));
		count++;
	}
	return (-1);
}

/**
 ** Create a token of a pipe
 **/

static int	tokenize_pipe(char **tok, t_que **lex)
{
	if (**tok != '\0')
		push_que(0, *tok, lex);
	if (*tok)
		free(*tok);
	(*tok) = ft_strdup("|");
	if (*tok)
	{
		push_que(0, *tok, lex);
		free(*tok);
	}
	(*tok) = ft_strdup("\0");
	return (0);
}

/**
 ** Create a token of the redirection < << > >>
 **/

static int	tokenize_red(char **tok, char *line, t_que **lex)
{
	int	out;

	if (**tok != '\0')
		push_que(0, *tok, lex);
	if (*tok)
		free(*tok);
	if (line[0] == '<' && line[1] == '<')
		(*tok) = ft_strdup("<<");
	else if (line[0] == '>' && line[1] == '>')
		(*tok) = ft_strdup(">>");
	else if (line[0] == '<')
		(*tok) = ft_strdup("<");
	else if (line[0] == '>')
		(*tok) = ft_strdup(">");
	if (*tok)
	{
		push_que(0, *tok, lex);
		free(*tok);
	}
	out = ft_strlen(*tok);
	(*tok) = ft_strdup("\0");
	return (out - 1);
}

/**
 ** Identify special char that is valid
 **/

static int	special_char(int x, char *line, char **token, t_que **lex)
{
	if (line[x] == '\'' && close_quotes('\'', line + x))
		x += add_to_quote('\'', token, line + x, lex);
	else if (line [x] == '\"' && close_quotes('\"', line + x))
		x += add_to_quote('\"', token, line + x, lex);
	else if (line[x] == '|')
		x += tokenize_pipe(token, lex);
	else if (line[x] == '<' || line[x] == '>')
		x += tokenize_red(token, line + x, lex);
	else if (line[x] == ' ' && (**token) != '\0')
	{
		push_que(0, *token, lex);
		free(*token);
		(*token) = ft_strdup("\0");
	}
	else if (line[x] != ' ')
		do_join(1, token, ft_charstr(line[x]));
	return (x);
}

/**
 ** Tokenize the line read
 **/

void	call_lexer(char *line, t_que **lex)
{
	char	*token;
	int		x;

	token = ft_strdup("\0");
	x = 0;
	while (line[x])
	{
		x = special_char(x, line, &token, lex);
		x++;
	}
	if (*token != '\0')
		push_que(0, token, lex);
	free(token);
}
