#include "../koala.h"

/**
 ** Loop while sin quote is not found
 **/

static void	loop_sinquote(int *num, char *beg, char *end)
{
	if (!(end > beg && *(end - 1) == '\\' && (*num) == -1))
		(*num) *= -1;
}

/**
 ** Push each line separated by ; in a queue
 **/

static void	loop_semicolon(int back, char **beg, char **end, t_que **tail)
{
	(**end) = '\0';
	if (back != 0)
		*(*end - 1) = '\0';
	if (**beg)
		push_que(0, *beg, tail);
	(*beg) = (*end) + 1;
}

/**
 ** Check command line considering \ " ' ;
 **/

void	check_command_line(char *line, t_que **tail)
{
	char	*beg;
	char	*end;
	int		sin;
	int		dob;
	int		back;

	beg = line;
	end = line;
	sin = -1;
	dob = -1;
	while (*end)
	{
		back = look_back_slash(beg, end - 1);
		if ((*end) == '\"' && sin == -1 && back == 0)
			dob *= -1;
		else if ((*end) == '\'' && dob == -1 && back == 0)
			loop_sinquote(&sin, beg, end);
		else if ((*end) == ';' && back == 0 && dob == -1 && sin == -1)
			loop_semicolon(back, &beg, &end, tail);
		end++;
	}
	if (*beg)
		push_que(0, beg, tail);
}
