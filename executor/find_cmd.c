#include "../koala.h"

static void	create_argv(char ***argv, t_que *cmd)
{
	t_que	*tmp;
	int		count;

	count = 0;
	tmp = cmd;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	(*argv) = (char **)malloc(sizeof(char *) * count);
	count = 0;
	tmp = cmd;
	while (tmp)
	{
		(*argv)[count++] = ft_strdup(tmp->line);
		tmp = tmp->next;
	}
	(*argv)[count] = NULL;
}

static void	free_argv(char ***argv, t_que *cmd)
{
	t_que	*tmp;
	int		count;

	tmp = cmd;
	count = 0;
	while (tmp)
	{
		free((*argv)[count++]);
		tmp = tmp->next;
	}
	free(*argv);
}

static void	execute_cmd(char *path, char ***argv, char ***envp, t_que *cmd)
{
	if (execve(path, (*argv), (*envp)) != -1)
	{
		free_argv(argv, cmd);
		exit(0);
	}
}

void	find_path_cmd(char **div_path, char ***envp, t_que *cmd)
{
	char	**argv;
	char	*path;
	char	*tmp;
	int		count;

	count = 0;
	create_argv(&argv, cmd);
	execute_cmd(cmd->line, &argv, envp, cmd);
	while (div_path[count])
	{
		path = ft_strjoin(div_path[count], "/");
		tmp = path;
		path = ft_strjoin(path, cmd->line);
		execute_cmd(path, &argv, envp, cmd);
		free(tmp);
		free(path);
		count++;
	}
	free_argv(&argv, cmd);
	exit(0);
}
