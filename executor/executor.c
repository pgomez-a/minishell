#include "../koala.h"

static void	create_argc(char ***argc, t_que *cmd)
{
	t_que	*tmp;
	int	count;

	count = 0;
	tmp = cmd;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	(*argc) = (char **)malloc(sizeof(char *) * count);
	count = 0;
	tmp = cmd;
	while (tmp)
	{
		(*argc)[count++] = ft_strdup(tmp->line);
		tmp = tmp->next;
	}
	(*argc)[count] = NULL;
}

static void	free_argc(char ***argc, t_que *cmd)
{
	t_que	*tmp;
	int	count;

	tmp = cmd;
	count = 0;
	while (tmp)
	{
		free((*argc)[count++]);
		tmp = tmp->next;
	}
	free(*argc);
}

static void	execute_cmd(char **div_path, t_que *cmd)
{
	char	**argc;
	char	*path;
	char	*tmp;
	int	count;

	count = 0;
	printf("\n"); // Salto de línea porque prompt no lo hace
	create_argc(&argc, cmd);
	if (execve(cmd->line, argc, NULL) != -1)
	{
		free_argc(&argc, cmd);
		exit(0);
	}
	while (div_path[count])
	{
		path = ft_strjoin(div_path[count], "/");
		tmp = path;
		path = ft_strjoin(path, cmd->line);
		if (execve(path, argc, NULL) != -1)
		{
			free_argc(&argc, cmd);
			exit(0);
		}
		free(tmp);
		free(path);
		count++;
	}
	free_argc(&argc, cmd);
	exit(0);
}

static void	look_for_cmd(char **div_path, t_que *cmd)
{
	if (cmd && cmd->line)
	{
		if (fork() > 0)
			wait(NULL);
		else
			execute_cmd(div_path, cmd);
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
			look_for_cmd(div_path, tmp->cmd);
			tmp = tmp->next;
		}
	}
	free_env(path, div_path);
}
