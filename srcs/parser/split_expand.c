#include "../../inc/koala.h"

static void	empty_variable(char *variable, t_que **var)
{
	if (!variable)
	{
		free((*var)->line);
		(*var)->line = ft_strdup("\0");
	}
}

void	split_for_expansion(char **result, t_que **var)
{
	t_que	*next;
	char	**spaces;
	int		x;

	spaces = ft_split(*result, ' ');
	next = (*var)->next;
	(*var)->next = NULL;
	x = 0;
	while (spaces[x])
	{
		if (x == 0)
		{
			free((*var)->line);
			(*var)->line = ft_strdup(spaces[x]);
		}
		else
		{
			push_que(0, spaces[x], var);
			(*var) = (*var)->next;
		}
		free(spaces[x++]);
	}
	empty_variable(spaces[0], var);
	free(spaces);
	(*var)->next = next;
}
