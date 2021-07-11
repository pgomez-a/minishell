#include "../../inc/koala.h"

void	reset_fds(int mode)
{
	static int	input;
	static int	output;
	static int	error_fd;

	if (mode)
	{
		input = dup(STDIN_FILENO);
		output = dup(STDOUT_FILENO);
		error_fd = dup(STDERR_FILENO);
	}
	else
	{
		dup2(input, STDIN_FILENO);
		dup2(output, STDOUT_FILENO);
		dup2(error_fd, STDERR_FILENO);
		close(input);
		close(output);
		close(error_fd);
	}
}

void	manege_pipe(t_cmd *tmp, int fd[2], pid_t pid)
{
	static int	i = 0;
	static int	next_input = 0;
	static int	fd_out = 0;

	if (!i)
		reset_fds(1);
	if (i)
	{
		dup2(next_input, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(next_input);
	}
	if (tmp->next)
	{
		if (!pid)
			close(fd[0]);
		fd_out = dup(STDOUT_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		next_input = fd[0];
		i = 1;
	}
	else
		i = 0;
}

pid_t	multi_process_manegment(pid_t **pids)
{
	pid_t	*tmp;
	int		size;
	int		j;

	size = 0;
	if (*pids)
		while ((*pids)[size])
			size++;
	tmp = *pids;
	*pids = malloc(sizeof(pid_t) * (++size + 1));
	if (!(*pids))
		exit(1);
	j = 0;
	while (j < (size - 1))
	{
		(*pids)[j] = tmp[j];
		j++;
	}
	(*pids)[size - 1] = fork();
	(*pids)[size] = 0;
	if (tmp)
		free(tmp);
	return ((*pids)[size - 1]);
}

void	wait_several_processes(pid_t *pids)
{
	int	size;
	int	i;
	int	wstatus;

	if (pids)
	{
		size = 0;
		while (pids[size])
			size++;
		i = 0;
		while (i < size)
			waitpid(pids[i++], &wstatus, 0);
		free(pids);
		if (WIFEXITED(wstatus))
			get_errorvar(WEXITSTATUS(wstatus), 0);
	}
}
