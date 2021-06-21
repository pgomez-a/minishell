#include "koala.h"

void	init_cmd(t_cmd **par)
{
	(*par)->cmd = NULL;
	(*par)->red = NULL;
	(*par)->next = NULL;
	(*par)->err = 0;
}
