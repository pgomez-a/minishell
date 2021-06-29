#include "../koala.h"

static void	ko_echo(char ***argv)
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

static void	ko_pwd()
{
	printf("%s\n", getenv("PWD"));
}

static void	ko_exit()
{
	init_terminal(0, 3);
	system("leaks koala");
	exit(0); //this exit not clean, we need to pass all the allocated memory to be freed
}

void	exec_builtin(char ***argv)
{
	if (!ft_strcmp("echo", (*argv)[0]))
		ko_echo(argv);
	else if (!ft_strcmp("pwd", (*argv)[0]))
		ko_pwd();
	else if (!ft_strcmp("exit", (*argv)[0]))
		ko_exit();
}
