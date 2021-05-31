#include "koala.h"

void	check_if_push(int mode, int *x, char **out, t_que **lex)
{
	if (*(*out) != '\0')
		push_que(x[1], *out, lex);
	free(*out);
	if (mode == 1)
	{
		(*out) = ft_strdup("");
		x[1] = 0;
	}
	else if (mode == 0)
		(*out) = NULL;
}

void	check_if_join(int *x, int back, char *line, char **out)
{
	char	*str;

	str = ft_charstr(line[x[0]]);
	if (line[x[0]] != '\n' || (line[x[0]] == '\n' && back == 0))
		do_join(out, str);
	if (line[x[0]] == '$' && back == 0 && line[x[0] + 1])
		x[1] = 1;
	free(str);
}

int	check_sin_quote(int *x, char *line, char **out, t_que **lex)
{
	int	back;

	back = look_back_slash(line, line + x[0] - 1);
	if (back == 0)
	{
		check_if_join(x, back, line, out);
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
		while ((line[x[0]] && line[x[0]] != '\"')
			|| (line[x[0]] == '\"' && back != 0))
		{
			if ((line[x[0]] == '\\' && line[x[0] + 1] != '\n'
					&& line[x[0] + 1] != '$' && back == 0)
				|| line[x[0]] != '\\')
				check_if_join(x, back, line, out);
			if (line[x[0]] == '$' && back == 0 && line[x[0] + 1])
				op++;
			x[0]++;
			back = look_back_slash(line, line + x[0] - 1);
		}
		x[1] = op;
		check_if_push(1, x, out, lex);
		return (x[0]);
	}
	check_if_join(x, back, line, out);
	return (x[0]);
}

int	check_redirections(int *x, char *line, char **out, t_que **lex)
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
