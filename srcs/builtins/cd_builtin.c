#include "../../inc/koala.h"

static void	change_pwd_value(char ***envp)
{
	char	**argv;
	char	*pwd;

	argv = malloc(sizeof(char *) * 3);
	argv[0] = "export";
	pwd = koala_getcwd();
	argv[1] = ft_strjoin("PWD=", pwd);
	argv[2] = 0;
	koala_export(envp, argv);
	free(argv[1]);
	free(argv);
	free(pwd);
}

static int	change_dir(const char *new_dir, char ***envp)
{
	if (chdir(new_dir))
	{
		if (errno == ENOENT)
		{
			printf("cd: no such file or directory: %s\n", new_dir);
			get_errorvar(errno, 0);
		}
		else if (errno == ENOTDIR)
		{
			printf("cd not a directory: %s\n", new_dir);
			get_errorvar(errno, 0);
		}
	}
	else
		change_pwd_value(envp);
	return (errno);
}

int	koala_cd(char **argv, char ***envp)
{
	char	*next_dir;

	if (!argv[1])
		next_dir = koala_getenv("HOME", *envp);
	else
		next_dir = argv[1];
	return (change_dir(next_dir, envp));
}
