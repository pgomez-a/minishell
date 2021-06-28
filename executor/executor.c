#include "../koala.h"

static void	look_for_cmd(char **div_path, t_que *red, t_que *cmd)
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
	if (cmd && cmd->line && err != -1)
	{
		if (fork() > 0)
			wait(NULL);
		else
			find_path_cmd(div_path, cmd);
	}
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

void	call_executor(t_cmd **par)
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
			look_for_cmd(div_path, tmp->red, tmp->cmd);
			tmp = tmp->next;
		}
	}
	free_env(path, div_path);
}
