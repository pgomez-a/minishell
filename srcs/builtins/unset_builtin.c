#include "../../inc/koala.h"

static void	delete_env(char ***envp, int pos)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	while ((*envp)[i])
		i++;
	new_envp = malloc(sizeof(char *) * i);
	if (!new_envp)
		exit(1);
	new_envp[i - 1] = 0;
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
	int		i;
	int		j;
	char	*variable;
	char	*value;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while ((*envp)[j])
		{
			if (!compare_env_var((*envp)[j], argv[i]))
			{
				split_env((*envp)[i], &variable, &value);
				if (!compare_env_var("_=", variable))
					delete_env(envp, j);
				free(variable);
				if (value)
					free(value);
				break ;
			}
			j++;
		}
		i++;
	}
}
