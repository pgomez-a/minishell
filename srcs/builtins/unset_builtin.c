#include "../../inc/koala.h"

static void delete_env(char ***envp, int pos)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	while((*envp)[i])
		i++;
	new_envp = malloc(sizeof(char *) * i);
	new_envp[i] = 0;
	i = 0;
	j = 0;
	while ((*envp)[j])
	{
		if (j != pos)
			new_envp[i++] = (*envp)[j];
		else
			free((*envp)[j]);
		j++;
	}
	free(*envp);
	*envp = new_envp;
}

void	koala_unset(char ***envp, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while ((*envp)[j])
		{
			if (!compare_env_var((*envp)[j], argv[i]))
			{
				delete_env(envp, j);
				break ;
			}
			j++;
		}
		i++;
	}
}
