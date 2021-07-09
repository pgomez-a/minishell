#include "../../inc/koala.h"

static void	koala_echo(char **argv)
{
	unsigned int	i;
	int				n;

	i = 1;
	n = 0;
	while (argv[i] && !ft_strcmp(argv[i], "-n"))
		i++;
	if (i > 1)
		n = 1;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[++i])
			write(1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
}

static void	koala_pwd(void)
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

static int	koala_env(char **argv, char ***envp)
{
	int	i;

	if (argv[1])
	{
		printf("env: «%s»: no existe el archivo o el directorio\n", argv[1]);
		return (127);
	}
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strchr((*envp)[i], '='))
			printf("%s\n", (*envp)[i]);
		i++;
	}
	return (0);
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
		exit_status = koala_env(*argv, envp);
	else if (!ft_strcmp("export", (*argv)[0]))
		koala_export(envp, *argv);
	else if (!ft_strcmp("unset", (*argv)[0]))
		koala_unset(envp, *argv);
	return (exit_status);
}
