#include "../koala.h"

static void	koala_echo(char ***argv)
{
	unsigned int	i;

	i = 1;
	if (!ft_strcmp((*argv)[i], "-n"))
		i++;
	while ((*argv)[i])
	{
		ft_putstr_fd((*argv)[i], 0);
		if ((*argv)[++i])
			write(1, " ", 1);
	}
	if (ft_strcmp((*argv)[1], "-n"))
		printf("\n");
}

static void	koala_pwd()
{
	printf("%s\n", getenv("PWD"));
}

static void	koala_exit(t_dlist *history)
{
	save_history(&history);
	init_terminal(0, 3);
	system("leaks koala");
	exit(0); //this exit not clean, we need to pass all the allocated memory to be freed
}

void	exec_builtin(t_dlist *history, char ***argv, char ***envp)
{
	if (!ft_strcmp("echo", (*argv)[0]))
		koala_echo(argv);
	else if (!ft_strcmp("pwd", (*argv)[0]))
		koala_pwd();
	else if (!ft_strcmp("exit", (*argv)[0]))
		koala_exit(history);
	else if (!ft_strcmp("cd", (*argv)[0]))
		koala_cd();
	else if (!ft_strcmp("env", (*argv)[0]))
		koala_env(envp, argv);
}
