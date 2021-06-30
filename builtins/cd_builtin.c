#include "../koala.h"

static void	change_dir(const char *path, const char *new_dir)
{
	if (chdir(new_dir))
	{
		if (errno == ENOENT)
			printf("cd: no such file or directory: %s\n", new_dir);
		else if (errno == ENOTDIR)
			printf("cd not a directory: %s\n", new_dir);
	}
}

void	koala_cd(char **argv)
{
	char	*path;
	int		size;

	if (!argv[1])
		return ;
	size = 10;
	path = malloc(sizeof(char) * 16);
	while (!getcwd(path, size))
	{
		free(path);
		size *= 2;
		path = malloc(sizeof(char) * size);
	}
	if (argv[2])
		printf("cd: string not in pwd: %s\n", argv[1]);
	else
		change_dir(path, argv[1]);
	free(path);
}
