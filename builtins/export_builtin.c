#include "../koala.h"

static int	change_existing_env(char ***envp, char *variable, char *value)
{
	int		j;
	int		done;
	char	*tmp;

	j = 0;
	done = 0;
	while ((*envp)[j] && !done)
	{
		if ((!ft_strncmp((*envp)[j], variable, ft_strlen(variable))) && value) //necesitas unn strcmp de verdad
		{
			free((*envp)[j]);
			if (value)
				do_join(1, &variable, value);
			(*envp)[j] = variable;
			variable = 0;
			value = 0;
			done = 1;
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

static void	split_env(const char *string, char **variable, char **value)
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

static void	export_value_mod(char ***envp, char **argv)
{
	int		i;
	char	*variable;
	char	*value;
	char	*tmp;

	i = 1;
	while (argv[i])
	{
		split_env(argv[i], &variable, &value);
		if (!change_existing_env(envp, variable, value))
			add_env(envp, ft_strdup(argv[i]));
		i++;
	}
}

void	koala_export(char ***envp, char **argv)
{
	int		i;
	char	*variable;
	char	*value;

	i = 0;
	if (!argv[1])
	{
		while ((*envp)[i])
		{
			split_env((*envp)[i++], &variable, &value);
			printf("declare -x %s", variable);
			if (ft_strchr(variable, '='))
				printf("\"%s\"", value);
			printf("\n");
			free(variable);
			if (value)
				free(value);
		}
	}
	else
		export_value_mod(envp, argv);
}
