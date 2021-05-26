#include "queue.h"

t_que	*init_que(char *line)
{
	t_que	*que;

	que = (t_data *)malloc(sizeof(t_data));
	if (!que)
		return (0);
	que->line = ft_strdup(line);
	que->next = NULL;
	return (que);
}

void	push_que(char *line, t_que **que)
{
	t_que	*tmp;

	if (*que)
	{
		tmp = *que;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_que *)malloc(sizeof(t_que));
		tmp->next->line = ft_strdup(line);
		tmp->next->next = NULL;
	}
}

char	*pop_que(t_que **que)
{
	t_que	*tmp;
	char	*out;

	out = NULL;
	if (*data)
	{
		tmp = *data;
		(*data) = (*data)->next;
		out = ft_strdup(tmp->line);
		free(tmp->line);
		free(tmp);
		tmp = NULL;
	}
	return (out);
	
}
