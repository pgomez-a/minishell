#include "../koala.h"

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

static void	change_dir(const char *new_dir, char ***envp)
{
	if (chdir(new_dir))
	{
		if (errno == ENOENT)
			printf("cd: no such file or directory: %s\n", new_dir);
		else if (errno == ENOTDIR)
			printf("cd not a directory: %s\n", new_dir);
	}
	else
		change_pwd_value(envp);
}

void	koala_cd(char **argv, char ***envp)
{
	char	*path;

	if (!argv[1])
		return ;
	path = koala_getcwd();
	if (argv[2])
		printf("cd: string not in pwd: %s\n", argv[1]);
	else
		change_dir(argv[1], envp);
	free(path);
}
