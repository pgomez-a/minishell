#include "../koala.h"

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

static void	look_for_cmd(char **div_path, char ***envp, t_que *cmd)
{
	int	i;
	char	**builtins; //does not change, so maybe its better to charge it earlier and free when koala closes
	char	**argv;

	if (!cmd || !cmd->line)
		return ;
	i = 0;
	builtins = ft_split(M_IMPLEMENTED_BUILTINS, ' ');
	while (builtins[i])
	{
		if (!ft_strcmp(builtins[i], cmd->line))
		{
			create_argv(&argv, cmd);
			exec_builtin(&argv);
			free_split(builtins);
			free_argv(&argv);
			return ;
		}
		i++;
	}
	free_split(builtins);
	if (fork() > 0)
		wait(NULL);
	else
		find_path_cmd(div_path, envp, cmd);
}

static void	set_red_fd(char **div_path, char ***envp, t_que *red, t_que *cmd)
{
	int	save_in;
	int	save_out;
	int	save_err;
	int	err;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	save_err = dup(STDERR_FILENO);
	err = 0;
	if (red)
		err = look_for_red(save_out, red);
	if (err != -1)
		look_for_cmd(div_path, envp, cmd); //preguntar a pablo que
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	dup2(save_err, STDERR_FILENO);
	close(save_in);
	close(save_out);
	close(save_err);
}

static void	free_env(char *path, char **div_path)
{
	int	count;

	count = 0;
	while (div_path[count])
		free(div_path[count++]);
	free(div_path);
	free(path);
}

void	call_executor(char ***envp, t_cmd **par)
{
	t_cmd	*tmp;
	char	*path;
	char	**div_path;
	int		mode;

	path = ft_strdup(getenv("PATH"));
	div_path = ft_split(path, ':');
	mode = 0;
	if (*par)
	{
		mode = (*par)->err;
		tmp = *par;
		while (tmp && mode != 1)
		{
			set_red_fd(div_path, envp, tmp->red, tmp->cmd);
			tmp = tmp->next;
		}
	}
	free_env(path, div_path);
}
