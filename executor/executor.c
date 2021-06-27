#include "../koala.h"

static void	look_for_cmd(char **div_path, t_que *cmd)
{
	if (cmd && cmd->line)
	{
		if (fork() > 0)
			wait(NULL);
		else
			find_path_cmd(div_path, cmd);
	}
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
		while (tmp && mode != -1)
		{
			look_for_cmd(div_path, tmp->cmd);
			tmp = tmp->next;
		}
	}
	free_env(path, div_path);
}
