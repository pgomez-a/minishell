#include "../koala.h"

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

static void	koala_exit(t_dlist *history)
{
	save_history(&history);
	init_terminal(0, 3);
	system("leaks koala");
	exit(0); //this exit not clean, we need to pass all the allocated memory to be freed
}

static void	koala_env(char ***envp, char ***argv)
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

void	exec_builtin(t_dlist *history, char ***argv, char ***envp)
{
	if (!ft_strcmp("echo", (*argv)[0]))
		koala_echo(*argv);
	else if (!ft_strcmp("pwd", (*argv)[0]))
		koala_pwd();
	else if (!ft_strcmp("exit", (*argv)[0]))
		koala_exit(history);
	else if (!ft_strcmp("cd", (*argv)[0]))
		koala_cd(*argv, envp);
	else if (!ft_strcmp("env", (*argv)[0]))
		koala_env(envp, argv);
	else if (!ft_strcmp("export", (*argv)[0]))
		koala_export(envp, *argv);
	else if (!ft_strcmp("unset", (*argv)[0]))
		koala_unset(envp, *argv);
}
