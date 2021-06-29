#include "../koala.h"

void	koala_env(char ***envp, char ***argv)
{
	int	i;

	i = 0;
	if (!((*argv)[1]))
	{
		while ((*envp)[i])
			printf("%s\n", (*envp)[i++]);
	}
	else
	{
		i = 0;
		// while ((*argv)[i])
		// 	modify_envp(envp, (*argv)[i++]);

	}
}
