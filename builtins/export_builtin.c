#include "../koala.h"

static int	change_existing_env(char ***envp, char *variable, char *value)
{
	int		j;
	int		done;

	j = 0;
	done = 0;
	while ((*envp)[j] && !done)
	{
		if (!compare_env_var((*envp)[j], variable))
		{
			done = 1;
			if (value)
			{
				free((*envp)[j]);
				do_join(1, &variable, value);
				(*envp)[j] = variable;
				variable = 0;
				value = 0;
			}
		}
		j++;
	}
	if (variable)
		free(variable);
	if (value)
		free(value);
	return (done);
}

static void	add_env(char ***envp, char *argv)
{
	int		size;
	char	**new_envp;

	size = 0;
	while ((*envp)[size])
		size++;
	new_envp = malloc(sizeof(char *) * (size + 2));
	new_envp = ft_memcpy(new_envp, *envp, sizeof(char *) * (size + 2));
	free(*envp);
	*envp = new_envp;
	new_envp[size] = argv;
	new_envp[size + 1] = 0;
}

void	split_env(const char *string, char **variable, char **value)
{
	char	*equal;

	equal = ft_strchr(string, '=');
	if (equal)
	{
		*variable = ft_substr(string, 0, equal + 1 - string);
		*value = ft_strdup(equal + 1);
	}
	else
	{
		*variable = ft_strdup(string);
		*value = 0;
	}
}

void	koala_export(char ***envp, char **argv)
{
	int		i;
	char	*variable;
	char	*value;
	char	*tmp;

	if (!argv[1])
		print_export(*envp);
	else
	{
		i = 1;
		while (argv[i])
		{
			split_env(argv[i], &variable, &value);
			if (!change_existing_env(envp, variable, value))
				add_env(envp, ft_strdup(argv[i]));
			i++;
		}
	}
}
