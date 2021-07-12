#include "../inc/koala.h"

static void	free_cmd(t_cmd **par)
{
	while ((*par)->cmd != NULL)
		free(pop_que(&((*par)->cmd)));
	while ((*par)->red != NULL)
		free(pop_que(&((*par)->red)));
}

static void	free_parser(t_cmd **par)
{
	t_cmd	*tmp;

	while (*par != NULL)
	{
		free_cmd(par);
		tmp = *par;
		(*par) = (*par)->next;
		free(tmp);
		tmp = NULL;
	}
}

static void	clean_par(t_cmd **par)
{
	t_que	*tmp;
	t_que	*prev;
	t_que	*empty;

	if ((*par) && (*par)->cmd)
	{
		tmp = (*par)->cmd;
		while (tmp)
		{
			if (tmp->op == 0 && *(tmp->line) == '\0')
			{
				empty = tmp->next;
				prev->next = empty;
				free(tmp->line);
				free(tmp);
				tmp = NULL;
				tmp = prev;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

/**
 ** Calls the lexer, the parser and the executor programs
 **/

void	man_command_line(t_dlist *history, char ***envp)
{
	t_que	*lex;
	t_cmd	*par;

	if (history->content)
	{
		lex = NULL;
		par = (t_cmd *)malloc(sizeof(t_cmd));
		if (!par)
			exit(1);
		init_cmd(&par);
		call_lexer(history->content, &lex);
		call_parser(&lex, &par);
		call_env(&par, *envp);
		clean_par(&par);
		if (par)
			call_executor(history, envp, &par);
		free_parser(&par);
	}
}
