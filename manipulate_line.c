#include "koala.h"

/**
 ** Frees lexer queue
 **/

static void	free_lexer(t_que **lex)
{
	while (*lex)
	{
		ft_printf("%s\n", (*lex)->line);
		free(pop_que(lex));
	}
	ft_printf("\n");
}

/**
 ** Calls the lexer, the parser and the executor programs
 **/

void	man_command_line(t_que **tail)
{
	t_que	*lex;
	char	*line;

	while (*tail)
	{
		line = pop_que(tail);
		lex = NULL;
		//call_lexer(line, &lex);
		free_lexer(&lex);
		ft_printf("%s\n", line);
		free(line);
	}
}
