#include "../koala.h"

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
	int		file;
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

static void	look_for_cmd(t_dlist *history, char **div_path, char ***envp, t_que *cmd)
{
	char	**argv;

	if (!cmd || !cmd->line)
		return ;
	if (!is_builtin(cmd->line))
	{
		create_argv(&argv, cmd);
		exec_builtin(history, &argv, envp);
		free_argv(&argv);
		return ;
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	find_path_cmd(div_path, envp, cmd);
}

static void	set_red_fd(t_dlist *history, char ***envp, t_cmd *tmp)
{
	int		save_in;
	int		save_out;
	int		save_err;
	int		err;
	char	**div_path;

	div_path = ft_split(koala_getenv("PATH", *envp), ':');
	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	save_err = dup(STDERR_FILENO);
	err = 0;
	if (tmp->red)
		err = look_for_red(save_out, tmp->red);
	if (err != -1)
		look_for_cmd(history, div_path, envp, tmp->cmd);
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	dup2(save_err, STDERR_FILENO);
	close(save_in);
	close(save_out);
	close(save_err);
	free_split(div_path);
	if (is_builtin(tmp->cmd->line) || tmp->next)
		exit (0);
}

void	call_executor(t_dlist *history, char ***envp, t_cmd **par)
{
	char	*path;
	t_cmd	*tmp;
	pid_t	pid;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	pid = 0;
	if (*par)
	{
		tmp = *par;
		while (tmp && tmp->err != 1)
		{
			if (is_builtin(tmp->cmd->line) || tmp->next)
				pid = fork();
			if (!pid)
				set_red_fd(history, envp, tmp);
			tmp = tmp->next;
		}
		if (pid)
			while (wait(NULL) != -1);
	}
}
