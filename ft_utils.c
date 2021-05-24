#include "prompt.h"

void	clear_cmand_struct(t_cmd *elem)
{
	free(elem->cmand);
	free(elem->tot);
	if (elem->argum)
		free(elem->argum);
}
