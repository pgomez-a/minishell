#include "../koala.h"

void	ctrlc(int num)
{
	kill(pid, SIGINT);
}
