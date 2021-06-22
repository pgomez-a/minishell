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

/**
 ** Create a token of a pipe
 **/

static int	tokenize_pipe(char **tok, t_que **lex)
{
	if (*tok)
	{
		if (**tok != '\0')
			push_que(0, *tok, lex);
		free(*tok);
		(*tok) = NULL;
	}
	(*tok) = ft_strdup("|");
	if (*tok)
	{
		push_que(0, *tok, lex);
		free(*tok);
		(*tok) = NULL;
	}
	(*tok) = ft_strdup("\0");
	return (0);
}

/**
 ** Create a token of the redirection < << > >>
 **/

static int	tokenize_red(char *line, char **tok, t_que **lex)
{
	int	out;

	if (*tok)
	{
		if (**tok != '\0')
			push_que(0, *tok, lex);
		free(*tok);
		(*tok) = NULL;
	}
	if (line[0] == '<' && line[1] == '<')
		(*tok) = ft_strdup("<<");
	else if (line[0] == '>' && line[1] == '>')
		(*tok) = ft_strdup(">>");
	else if (line[0] == '<')
		(*tok) = ft_strdup("<");
	else if (line[0] == '>')
		(*tok) = ft_strdup(">");
	out = 0;
	if (*tok)
	{
		out = ft_strlen(*tok);
		push_que(0, *tok, lex);
		free(*tok);
		(*tok) = NULL;
	}
	(*tok) = ft_strdup("\0");
	return (out - 1);
}

/**
 ** Create a token for closed quotes
 **/

static int	tokenize_quotes(char quot, char *line, char **tok, t_que **lex)
{
	int	count;

	if (*tok)
	{
		if (**tok != '\0')
			push_que(0, *tok, lex);
		free(*tok);
		(*tok) = NULL;
	}
	(*tok) = ft_strdup("\0");
	count = 1;
	while (line[count] != quot)
	{
		do_join(1, tok, ft_charstr(line[count]));
		count++;	
	}
	if (*tok)
	{
		if (quot == '\'' && **tok != '\0')
			push_que(2, *tok, lex);
		else
			push_que(1, *tok, lex);
		free(*tok);
		(*tok) = NULL;
	}
	(*tok) = ft_strdup("\0");
	return (count);
}

/**
 ** Identify special char that is valid
 **/

static int	special_char(int x, char *line, char **tok, t_que **lex)
{
	if ((line[x] == '\'' || line[x] == '\"') && close_quotes(x, line))
		x += tokenize_quotes(line[x], line + x, tok, lex);
	else if (line[x] == '|')
		x += tokenize_pipe(tok, lex);
	else if (line[x] == '<' || line[x] == '>')
		x += tokenize_red(line + x, tok, lex);
	else if (line[x] == ' ')
	{
		if (*tok)
		{
			if (**tok != '\0')
				push_que(0, *tok, lex);
			free(*tok);
			(*tok) = NULL;
		}
		(*tok) = ft_strdup("\0");
	}
	else if (line[x] != ' ')
		do_join(1, tok, ft_charstr(line[x]));
	return (x);
}

/**
 ** Tokenize the line read
 **/

void	call_lexer(char *line, t_que **lex)
{
	char	*tok;
	int		x;

	tok = ft_strdup("\0");
	x = 0;
	while (line[x])
	{
		x = special_char(x, line, &tok, lex);
		x++;
	}
	if (tok)
	{
		if (*tok != '\0')
			push_que(0, tok, lex);
		free(tok);
		tok = NULL;
	}
}
