#include "../koala.h"

static int	redirect_inp(t_que *red)
{
	int	file;

	file = open(red->line, O_RDONLY, 0777);
	if (file < 0)
	{
		printf("koala: no such file or directory: %s\n", red->line);
		return (-1);
	}
	dup2(file, STDIN_FILENO);
	close(file);
	return (0);
}

static int	redirect_add(t_que *red)
{
	int	file;

	file = open(red->line, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (file < 0)
	{
		printf("koala: can't operate with %s\n", red->line);
		return (-1);
	}
	dup2(file, STDOUT_FILENO);
	dup2(file, STDERR_FILENO);
	close(file);
	return (0);
}

static int	redirect_app(t_que *red)
{
	int	file;

	file = open(red->line, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (file < 0)
	{
		printf("koala: can't operate with %s\n", red->line);
		return (-1);
	}
	dup2(file, STDOUT_FILENO);
	dup2(file, STDERR_FILENO);
	close(file);
	return (0);
}

int	look_for_red(t_que *red)
{
	t_que	*tmp;
	int		file;
	int		out;

	tmp = red;
	out = 0;
	while (tmp && out >= 0)
	{
		if (tmp->op == 1)
			out = redirect_inp(tmp);
		else if (tmp->op == 2)
			out = redirect_add(tmp);
		else if (tmp->op == 4)
			out = redirect_app(tmp);
		tmp = tmp->next;
	}
	return (out);
}
