#include "koala.h"

/**
 ** Set parameters of command table to NULL to be able to use
 ** that queues
 **/

void	init_cmd(t_cmd **par)
{
	(*par)->cmd = NULL;
	(*par)->red = NULL;
	(*par)->next = NULL;
	(*par)->err = 0;
}

/**
 ** Create a new row of the command table if a valir pipe is found
 **/

void	find_pipe(t_que **lex, t_cmd **par)
{
	if ((*lex)->next)
	{
		(*par)->next = (t_cmd *)malloc(sizeof(t_cmd));
		(*par) = (*par)->next;
		init_cmd(par);
	}
	else
		ft_printf("koala: parse error near '|'\n");
}

/**
 ** Set command of command table to op == 1 to identify a variable in
 ** expansion phase.
 **/

void	find_dollar(char *line, t_que **lex, t_cmd **par)
{
	t_que	*tmp;
	int	len;

	len = ft_strlen(line);
	if (len > 1)
	{
		push_que(0, line, &((*par)->cmd));
		len = 0;
		tmp = (*par)->cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->op = (*lex)->op;
	}
}

/**
 ** Check if a redirection is valid and if so put the type of red
 **/

int	find_red(int mode, char *line, t_que **lex, t_cmd **par)
{
	int	op;

	(*par)->err = 1;
	if (*lex)
	{
		free(pop_que(lex));
		if (*lex)
		{
			free(line);
			line = ft_strdup((*lex)->line);
			op = (*lex)->op;
			if (op == 0 || op > 0 && ft_strchr(line, '$'))
			{
				op = op << 2;
				mode |= op;
				push_que(mode, line, &((*par)->red));
				(*par)->err = 0;
				return (0);
			}
			ft_printf("koala: parse error near '%s'\n", line);
			return (1);
		}
	}
	ft_printf("koala: parse error near '\\n'\n");
	return (1);
}
