#include "../../inc/koala.h"

static void	koala_echo(char **argv)
{
	unsigned int	i;

	i = 1;
	if (argv[i] && !ft_strcmp(argv[i], "-n"))
		i++;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[++i])
			write(1, " ", 1);
	}
	if (argv[1] && ft_strcmp(argv[1], "-n"))
		printf("\n");
}

static void	koala_pwd()
{
	char	*path;

	path = koala_getcwd();
	printf("%s\n", path);
	free(path);
}

void	koala_exit(t_dlist *history)
{
	save_history(&history);
	init_terminal(0, 2);
	get_errorvar(0, 0);
	exit(0);
}

static void	koala_env(char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strchr((*envp)[i], '='))
			printf("%s\n", (*envp)[i]);
		i++;
	}
}

int	exec_builtin(t_dlist *history, char ***argv, char ***envp)
{
	int	exit_status;

	exit_status = 0;
	if (!ft_strcmp("echo", (*argv)[0]))
		koala_echo(*argv);
	else if (!ft_strcmp("pwd", (*argv)[0]))
		koala_pwd();
	else if (!ft_strcmp("exit", (*argv)[0]))
		koala_exit(history);
	else if (!ft_strcmp("cd", (*argv)[0]))
		exit_status = koala_cd(*argv, envp);
	else if (!ft_strcmp("env", (*argv)[0]))
		koala_env(envp);
	else if (!ft_strcmp("export", (*argv)[0]))
		koala_export(envp, *argv);
	else if (!ft_strcmp("unset", (*argv)[0]))
		koala_unset(envp, *argv);
	return (exit_status);
}
