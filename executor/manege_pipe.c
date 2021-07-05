# include "../koala.h"

static void	reset_fds(int mode)
{
	static int	input;
	static int	output;
	static int	error;

	if (mode)
	{
		input = dup(STDIN_FILENO);
		output = dup(STDOUT_FILENO);
		errno = dup(STDERR_FILENO);
	}
	else
	{
		dup2(input, STDIN_FILENO);
		dup2(output, STDOUT_FILENO);
		dup2(error, STDERR_FILENO);
	}
}

void	manege_pipe(t_cmd *tmp, int fd[2], pid_t pid)
{
	static int	i = 0;
	static int	next_input = 0;
	static int	previous_output = 0;

	if (!i)
		reset_fds(1);
	if (i)
	{
		close(previous_output);
		dup2(next_input, STDIN_FILENO);
	}
	if (tmp->next)
	{
		if (!pid)
			close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		dup2(fd[1], STDERR_FILENO);
		next_input = fd[0];
		previous_output = fd[1];
		i = 1;
	}
	else
	{
		i = 0;
		reset_fds(0);
	}
}
