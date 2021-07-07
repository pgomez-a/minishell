#include "../../inc/koala.h"

void	init_cmd(t_cmd **par)
{
	(*par)->cmd = NULL;
	(*par)->red = NULL;
	(*par)->next = NULL;
	(*par)->err = 0;
}

static void	manage_pipe(t_que **lex, t_cmd **lnode, t_cmd **par)
{
	if ((*lnode)->cmd == NULL && (*lnode)->red == NULL)
	{
		(*par)->err = 1;
		ft_printf("koala: syntax error near unexpected token `|\'\n");
	}
	else if (!(*lex)->next)
	{
		(*par)->err = 1;
		ft_printf("koala: syntax error near unexpected token `|\'\n");
	}
	else
	{
		(*lnode)->next = (t_cmd *)malloc(sizeof(t_cmd));
		(*lnode) = (*lnode)->next;
		init_cmd(lnode);
	}
}

static int	valid_red(t_que **lex)
{
	t_que	*tmp;

	tmp = (*lex)->next;
	if (!ft_strncmp("<\0", tmp->line, 2))
		return (1);
	if (!ft_strncmp(">\0", tmp->line, 2))
		return (1);
	if (!ft_strncmp("<<\0", tmp->line, 3))
		return (1);
	if (!ft_strncmp(">>\0", tmp->line, 3))
		return (1);
	return (0);
}

static void	manage_red(int mode, t_que **lex, t_cmd **lnode, t_cmd **par)
{
	if (((*lex)->next && (*lex)->next->op == 0 && valid_red(lex))
		|| !(*lex)->next)
	{
		(*par)->err = 1;
		if (mode == 1)
			ft_printf("koala: syntax error near unexpected token `<\'\n");
		else if (mode == 2)
			ft_printf("koala: syntax error near unexpected token `>\'\n");
		else if (mode == 3)
			ft_printf("koala: syntax error near unexpected token `<<\'\n");
		else if (mode == 4)
			ft_printf("koala: syntax error near unexpected token `>>\'\n");
	}
	else if (!ft_strncmp("|\0", (*lex)->next->line, 2))
	{
		ft_printf("koala: syntax error near unexpected token `|\'\n");
		(*par)->err = 1;
	}
	else
	{
		free(pop_que(lex));
		if ((*lex)->op == 2)
			mode *= -1;
		push_que(mode, (*lex)->line, &(*lnode)->red);
	}
}

void	call_parser(t_que **lex, t_cmd **par)
{
	t_cmd	*lnode;

	lnode = *par;
	while (*lex)
	{
		if ((*lex)->op != 0)
			push_que((*lex)->op, (*lex)->line, &(lnode->cmd));
		else if ((*par)->err == 0)
		{
			if (!ft_strncmp("|\0", (*lex)->line, 2))
				manage_pipe(lex, &lnode, par);
			else if (!ft_strncmp("<\0", (*lex)->line, 2))
				manage_red(1, lex, &lnode, par);
			else if (!ft_strncmp(">\0", (*lex)->line, 2))
				manage_red(2, lex, &lnode, par);
			else if (!ft_strncmp("<<\0", (*lex)->line, 3))
				manage_red(3, lex, &lnode, par);
			else if (!ft_strncmp(">>\0", (*lex)->line, 3))
				manage_red(4, lex, &lnode, par);
			else
				push_que((*lex)->op, (*lex)->line, &(lnode->cmd));
		}
		free(pop_que(lex));
	}
}
