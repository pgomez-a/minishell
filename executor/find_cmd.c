#include "../koala.h"

void	create_argc(char ***argc, t_que *cmd)
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
	(*argc) = (char **)malloc(sizeof(char *) * (count + 1));
	count = 0;
	tmp = cmd;
	while (tmp)
	{
		(*argc)[count++] = ft_strdup(tmp->line);
		tmp = tmp->next;
	}
	(*argc)[count] = NULL;
}

void	free_argc(char ***argc)
{
	int		count;

	count = 0;
	while ((*argc)[count])
		free((*argc)[count++]);
	free(*argc);
}

void	find_path_cmd(char **div_path, t_que *cmd)
{
	char	**argc;
	char	*path;
	char	*tmp;
	int		count;

	count = 0;
	create_argc(&argc, cmd);
	execve(path, (argc), NULL);
	while (div_path[count])
	{
		path = ft_strjoin(div_path[count], "/");
		tmp = path;
		path = ft_strjoin(path, cmd->line);
		execve(path, (argc), NULL);
		free(tmp);
		free(path);
		count++;
	}
	free_argc(&argc);
	exit(0);
}
