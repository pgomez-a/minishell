#include "../koala.h"

void	signal_handler(int signum)
{
	kill(pid, signum);
}
