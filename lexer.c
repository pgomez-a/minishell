#include "koala.h"

static void	check_space(char **out, t_que **lex)
{
	if (*(*out) != '\0')
		push_que(0, *out, lex);
	free(*out);
	(*out) = ft_strdup("");
}

static void	check_if_join(int x, int back, char *line, char **out)
{
	char	*str;

	str = ft_charstr(line[x]);
	if (line[x] != '\n' || (line[x] == '\n' && back == 0))
		do_join(out, str);
	free(str);
}

static int	check_sin_quote(int x, char *line, char **out, t_que **lex)
{
	int	back;

	back = look_back_slash(line, line + x - 1); 
	if (back == 0)
	{
		check_space(out, lex);
		x++;
		while (line[x] != '\'')
			check_if_join(x++, back, line, out);
		check_space(out, lex);
		return (x);
	}
	check_if_join(x, back, line, out);
	return (x);
}

static int	check_dob_quote(int x, char *line, char **out, t_que **lex)
{
	int	back;

	back = look_back_slash(line, line + x - 1);
	if (back == 0)
	{
		check_space(out, lex);
		x++;
		while ((line[x] && line[x] != '\"') || (line[x] == '\"' && back != 0))
		{
			if (line[x] != '\\' || (line[x] == '\\' && back == 1 && line[x + 1] != '\n'))
				check_if_join(x, back, line, out);
			x++;
			back = look_back_slash(line, line + x - 1);
		}
		check_space(out, lex);
		return (x);
	}
	check_if_join(x, back, line, out);
	return (x);
}

static int	check_redirections(int x, char *line, char **out, t_que **lex)
{
	int	back;

	back = look_back_slash(line, line + x - 1);
	if (back == 0)
	{
		check_space(out, lex);
		check_if_join(x, back, line, out);
		if (line[x] == '>' && line[x + 1] == '>')
			check_if_join(x++, back, line, out);
		check_space(out, lex);
		return (x);
	}
	check_if_join(x, back, line, out);
	return (x);
}

void	call_lexer(char *line, t_que **lex)
{
	char	*out;
	int		back;
	int		x;

	x = 0;
	back = 0;
	ft_printf("line: |%s|\n", line);
	out = ft_strdup("");
	while (line[x])
	{
		back = look_back_slash(line, line + x - 1);
		if (line[x] == '\'')
			x = check_sin_quote(x, line, &out, lex);
		else if (line[x] == '\"')
			x = check_dob_quote(x, line, &out, lex);
		else if (line[x] == '<' || line[x] == '>' || line[x] == '|')
			x = check_redirections(x, line, &out, lex);
		else if (line[x] == ' ' && back == 0)
			check_space(&out, lex);
		else if (line[x] != '\\' || (line[x] == '\\' && back != 0))
			check_if_join(x, back, line, &out);
		x++;
	}
	if (*out != '\0')
		push_que(0, out, lex);
	free(out);
	out = NULL;
}
