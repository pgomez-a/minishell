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
		init_cmd(&par);
		call_lexer(history->content, &lex);
		call_parser(&lex, &par);
		call_env(&par, *envp);
		call_executor(history, envp, &par);
		free_parser(&par);
	}
}
