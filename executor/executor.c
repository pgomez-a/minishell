#include "../koala.h"

static void	execute_cmd(char **div_path, t_que *cmd)
{
	char	*path;
	char	*line;
	char	*tmp;
	int	count;

	count = 0;
	if (cmd && cmd->line)
	{
			while (div_path[count] && count >= 0)
			{
				path = ft_strjoin(div_path[count], "/");
				tmp = path;
				path = ft_strjoin(path, cmd->line);
				if (execve("man", NULL, NULL) != -1)
				{
					printf("cmd: %s\n", div_path[count]);
					count = -9999;
				}
				free(tmp);
				free(path);
				count++;
			}
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
	int	mode;

	path = ft_strdup(getenv("PATH"));
	div_path = ft_split(path, ':');
	mode = 0;
	if (*par)
	{
		mode = (*par)->err;
		tmp = *par;
		while (tmp && mode != -1)
		{
			//execute_cmd(div_path, tmp->cmd);
			tmp = tmp->next;
		}
	}
	free_env(path, div_path);
}
