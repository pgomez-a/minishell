#include "../koala.h"

static void	ko_echo(char **argv)
{
	unsigned int	i;

	i = 1;
	while (argv[i])
		printf("%s", argv[i++]);
}

static void	ko_pwd()
{
	printf("%s", getenv("PWD"));
}

static void	ko_exit()
{
	exit(0); //this exit not clean, we need to pass all the allocated memory to be freed
}

void	exec_builtin(char **argv)
{
	if (ft_strcmp("echo", argv[0]))
		ko_echo(argv);
	else if (ft_strcmp("pwd", argv[0]))
		ko_pwd();
	else if (ft_strcmp("exit", argv[0]))
		ko_exit();
}
