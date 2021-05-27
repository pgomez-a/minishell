#include "minishell.h"

/**
 ** Lexer looks for pipes |
 **/

static int	look_pipes(int count, char *line, int *verif, t_que **lex)
{
	int	tmp;

	(*verif) = 2;
	line[count] = '\0';
	tmp = count;
	while (tmp && line[tmp - 1] && line[tmp - 1] != ' ')
		tmp--;
	if (tmp < count)
		push_que(line + tmp, lex);
	push_que("|", lex);
	return (count + 1);
}

/**
 ** Lexer looks for quotes ' & "
 **/

static int	look_quotes(char c, int count, char *line)
{
	count++;
	while (line[count] && line[count] != c)
		count++;
	return (count);
}

/**
 ** Lexer looks for redirections
 **/

static int	look_redirections(int count, char *line, int *verif, t_que **lex)
{
	char	*str;
	char	buff[2];
	int	tmp;

	(*verif = 2);
	buff[0] = line[count];
	buff[1] = '\0';
	line[count] = '\0';
	tmp = count;
	while (tmp && line[tmp - 1] && line[tmp - 1] != ' ')
		tmp--;
	if (tmp < count)
		push_que(line + tmp, lex);
	tmp = ++count;
	while (line[tmp] == ' ')
		tmp++;
	while (line[tmp] && line[tmp] != ' ')
		tmp++;
	line[tmp] = '\0';
	str = ft_strjoin(buff, line + count);
	push_que(str, lex);
	free(str);
	if (!line[tmp])
		return (tmp);
	return (tmp + 1);
}

/**
 ** Lexer looks for: | ' " < > >>
 **/

void	call_lexer(char *line, t_que **lex)
{
	int	x;
	int	t;
	int	verif;

	x = 0;
	t = 0;
	while (line[x])
	{
		verif = 0;
		while (line[x] && line[x] != ' ' && verif != 2)
		{
			verif = 1;
			if (line[x] == '|')
				x = look_pipes(x, line, &verif, lex);
			else if (line[x] == '\'' || line[x] == '\"')
				x = look_quotes(line[x], x, line);
			else if (line[x] == '<' || line[x] == '>')
				x = look_redirections(x, line, &verif, lex);
			else
				x++;
		}
		if (line[x] != '\0' && verif == 1)
			line[x++] = '\0';
		if (verif == 1)
			push_que(line + t, lex);
		while (line[x] == ' ')
			line[x++] = '\0';
		t = x;
	}
}
