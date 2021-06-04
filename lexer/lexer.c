#include "../koala.h"

/**
 ** Check if a redirection is valid and if so set op to 1
 **/

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

/**
 ** Check command line to tokenize it --> lexer
 **/

void	call_lexer(char *line, t_que **lex)
{
	char	*out;
	int		back;
	int		x[3];

	x[0] = 0;
	x[1] = 0;
	x[2] = 0;
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
