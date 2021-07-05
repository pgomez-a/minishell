#include "../koala.h"

void	charge_pipe_fds(t_que **pipe_fds)
{
	int		fd[2];

	pipe(fd);
	if (!(*pipe_fds))
		push_que(fd[1], "start", pipe_fds);
	else
		push_que(fd[1], 0, pipe_fds);
	push_que(fd[0], 0, pipe_fds);
}
