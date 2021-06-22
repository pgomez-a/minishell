#include "koala.h"

/**
 ** Create a token of a pipe
 **/

int	tokenize_pipe(char **tok, t_que **lex)
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
 ** Create a token for closed quotes
 **/

static void	check_push_quot(char quot, char **tok, t_que **lex)
{
	if (*tok)
	{
		if (quot == '\'' && (**tok) != '\0')
			push_que(2, *tok, lex);
		else
			push_que(1, *tok, lex);
		free(*tok);
		(*tok) = NULL;
	}
	(*tok) = ft_strdup("\0");
}

int	tokenize_quot(char quot, char *line, char **tok, t_que **lex)
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
	check_push_quot(quot, tok, lex);
	return (count);
}

/**
 ** Create a token of the redirection < << > >>
 **/

static int	check_push_red(char **tok, t_que **lex)
{
	int	out;

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

int	tokenize_red(char *line, char **tok, t_que **lex)
{
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
	return (check_push_red(tok, lex));
}
