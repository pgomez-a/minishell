#include "../../inc/koala.h"

static void	clean_argv(char ***argv)
{
	int		i;
	int		j;
	int		size;
	char	**new_argc;

	i = 0;
	size = 0;
	while ((*argv)[i])
	{
		if ((*((*argv)[i])))
			size++;
		i++;
	}
	i = 0;
	j = 0;
	new_argc = malloc(sizeof(char *) * (size + 1));
	while ((*argv)[i])
	{
		if (*((*argv)[i]))
			new_argc[j++] = (*argv)[i];
		else
			free((*argv)[i]);
		i++;
	}
	new_argc[j] = 0;
	free(*argv);
	*argv = new_argc;
}

void	create_argv(char ***argv, t_que *cmd)
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
	(*argv) = (char **)malloc(sizeof(char *) * (count + 1));
	if (!(*argv))
		exit(1);
	count = 0;
	tmp = cmd;
	while (tmp)
	{
		(*argv)[count] = ft_strdup(tmp->line);
		if (!((*argv)[count++]))
			exit(1);
		tmp = tmp->next;
	}
	(*argv)[count] = NULL;
	clean_argv(argv);
}

void	free_argv(char ***argc)
{
	int		count;

	count = 0;
	while ((*argc)[count])
		free((*argc)[count++]);
	free(*argc);
}

void	find_path_cmd(char **div_path, char ***envp, t_que *cmd)
{
	char	**argv;
	char	*path;
	char	*tmp;
	int		count;

	count = 0;
	create_argv(&argv, cmd);
	execve(cmd->line, argv, (*envp));
	if (div_path)
	{
		while (div_path[count])
		{
			path = ft_strjoin(div_path[count], "/");
			tmp = path;
			path = ft_strjoin(path, cmd->line);
			execve(path, argv, (*envp));
			free(tmp);
			free(path);
			count++;
		}
	}
	free_argv(&argv);
	printf("koala: %s: command not found\n", cmd->line);
	exit (127);
}
