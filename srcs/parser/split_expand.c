#include "../../inc/koala.h"

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
		free(spaces[x]);
		x++;
	}
	free(spaces);
	(*var)->next = next;
}
