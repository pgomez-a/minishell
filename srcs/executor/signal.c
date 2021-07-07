#include "../../inc/koala.h"

void	signal_handler(int signum)
{
	exit(signum);
}
