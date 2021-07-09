#include "../../inc/koala.h"

static int	is_builtin(char *cmd)
{
	int		i;
	char	**builtins;

	builtins = ft_split(M_IMPLEMENTED_BUILTINS, ' ');
	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp(builtins[i], cmd))
		{
			free_split(builtins);
			return (0);
		}
		i++;
	}
	free_split(builtins);
	return (1);
}

static int	look_for_red(int std_in, t_que *red)
{
	t_que	*tmp;
	int		out;

	tmp = red;
	out = 0;
	while (tmp && out >= 0)
	{
		if (tmp->op == 1)
			out = redirect_inp(tmp);
		else if (tmp->op == 2)
			out = redirect_add(tmp);
		else if (tmp->op == 3)
			out = redirect_rdin(std_in, tmp);
		else if (tmp->op == 4)
			out = redirect_app(tmp);
		tmp = tmp->next;
	}
	return (out);
}

static int	look_for_cmd(t_dlist *history, char ***envp, t_que *cmd)
{
	char	**argv;
	char	**div_path;
	int		exit_status;

	if (!cmd || !cmd->line)
		return (0);
	exit_status = 0;
	if (!is_builtin(cmd->line))
	{
		create_argv(&argv, cmd);
		exit_status = exec_builtin(history, &argv, envp);
		free_argv(&argv);
		return (exit_status);
	}
	div_path = ft_split(koala_getenv("PATH", *envp), ':');
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	find_path_cmd(div_path, envp, cmd);
	free_split(div_path);
	return (exit_status);
}

static void	set_red_fd(t_dlist *history, char ***envp, t_cmd *tmp, t_cmd *par)
{
	int		save_in;
	int		save_out;
	int		save_err;
	int		err;
	int		builtin_exit;

	builtin_exit = 0;
	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	save_err = dup(STDERR_FILENO);
	if (save_in == -1 || save_out == -1 || save_err == -1)
		exit(4);
	err = 0;
	if (tmp->red)
		err = look_for_red(save_out, tmp->red);
	if (err != -1)
		builtin_exit = look_for_cmd(history, envp, tmp->cmd);
	if ((dup2(save_in, STDIN_FILENO)) == -1
		|| (dup2(save_out, STDOUT_FILENO)) == -1
		|| (dup2(save_err, STDERR_FILENO)) == -1)
		exit(4);
	if (par->next)
		exit (builtin_exit);
}

void	call_executor(t_dlist *history, char ***envp, t_cmd **par)
{
	t_cmd	*tmp;
	pid_t	pid;
	pid_t	*pids;
	int		pipe_fd[2];

	pids = 0;
	tmp = *par;
	while (tmp && tmp->err != 1)
	{
		pid = 0;
		if ((tmp->cmd && is_builtin(tmp->cmd->line)) || (*par)->next)
		{
			if (tmp->next)
				pipe(pipe_fd);
			pid = multi_process_manegment(&pids);
		}
		manege_pipe(tmp, pipe_fd, pid);
		if (!pid)
			set_red_fd(history, envp, tmp, *par);
		tmp = tmp->next;
		reset_fds(0);
	}
	wait_several_processes(pids);
}
