#include "../koala.h"

static void	create_argc(char ***argc, t_que *cmd)
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
	int		count;

	tmp = cmd;
	count = 0;
	while (tmp)
	{
		free((*argc)[count++]);
		tmp = tmp->next;
	}
	free(*argc);
}

static void	execute_cmd(char *path, char ***argc, t_que *cmd)
{
	if (execve(path, (*argc), NULL) != -1)
	{
		free_argc(argc, cmd);
		exit(0);
	}
}

void	find_path_cmd(char **div_path, t_que *cmd)
{
	char	**argc;
	char	*path;
	char	*tmp;
	int		count;

	count = 0;
	printf("\n"); // Salto de linea porque el prompt no lo hace
	create_argc(&argc, cmd);
	execute_cmd(cmd->line, &argc, cmd);
	while (div_path[count])
	{
		path = ft_strjoin(div_path[count], "/");
		tmp = path;
		path = ft_strjoin(path, cmd->line);
		execute_cmd(path, &argc, cmd);
		free(tmp);
		free(path);
		count++;
	}
	free_argc(&argc, cmd);
	exit(0);
}
