#include "../../inc/koala.h"

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
	if (!(*tok))
		exit(1);
	if (*tok)
	{
		push_que(0, *tok, lex);
		free(*tok);
		(*tok) = NULL;
	}
	(*tok) = ft_strdup("\0");
	if (!(*tok))
		exit(1);
	return (0);
}

/**
 ** Create a token for closed quotes
 **/

static void	check_push_quot(char quot, char *line, char **tok, t_que **lex)
{
	if (*tok)
	{
		if (quot == '\'' && (**tok) != '\0')
		{
			if (!(*(line + 1)) || *(line + 1) == ' ')
				push_que(2, *tok, lex);
		}
		else if (!(*(line + 1)) || *(line + 1) == ' ')
			push_que(1, *tok, lex);
		if (!(*(line + 1)) || *(line + 1) == ' ')
		{
			free(*tok);
			(*tok) = NULL;
		}
	}
	if (!(*(line + 1)) || *(line + 1) == ' ')
		(*tok) = ft_strdup("\0");
	if (!(*tok))
		exit(1);
}

int	tokenize_quot(char quot, char *line, char **tok, t_que **lex)
{
	int	count;

	count = 1;
	while (line[count] != quot)
	{
		do_join(1, tok, ft_charstr(line[count]));
		count++;
	}
	if (line[count] == '\'' || line[count] == '\"')
		check_push_quot(quot, line + count, tok, lex);
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
	if (!(*tok))
		exit(1);
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
