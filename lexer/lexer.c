#include "../koala.h"

/**
 ** Identify special char that is valid
 **/

static int	special_char(int x, char *line, char **tok, t_que **lex)
{
	if ((line[x] == '\'' || line[x] == '\"') && close_quotes(x, line))
		x += tokenize_quot(line[x], line + x, tok, lex);
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
