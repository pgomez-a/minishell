#include "../../inc/koala.h"

static void	change_pwd_value(char ***envp)
{
	char	**argv;
	char	*pwd;

	argv = malloc(sizeof(char *) * 3);
	argv[0] = "export";
	argv[1] = ft_strjoin("OLDPWD=", koala_getenv("PWD", *envp));
	if (!(argv[1]))
		exit(1);
	argv[2] = 0;
	koala_export(envp, argv);
	free(argv[1]);
	pwd = koala_getcwd();
	argv[1] = ft_strjoin("PWD=", pwd);
	if (!(argv[1]))
		exit(1);
	argv[2] = 0;
	koala_export(envp, argv);
	free(argv[1]);
	free(pwd);
	free(argv);
}

static int	change_dir(const char *new_dir, char ***envp)
{
	if (chdir(new_dir))
		printf("koala: cd: %s: %s\n", new_dir, strerror(errno));
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
	if (change_dir(next_dir, envp))
		return (1);
	return (0);
}
