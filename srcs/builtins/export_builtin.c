#include "../../inc/koala.h"

static int	change_existing_env(char ***envp, char *variable, char *value)
{
	int		j;
	int		done;

	j = -1;
	done = 0;
	while ((*envp)[++j] && !done)
	{
		if (!compare_env_var((*envp)[j], variable))
		{
			done = 1;
			if (value && compare_env_var("_=", variable))
			{
				free((*envp)[j]);
				do_join(1, &variable, value);
				(*envp)[j] = variable;
				variable = 0;
				value = 0;
			}
		}
	}
	if (variable)
		free(variable);
	if (value)
		free(value);
	return (done);
}

int	add_env(char ***envp, char *argv)
{
	int		size;
	char	**new_envp;

	if (ft_strchr("0123456789", *argv))
	{
		free(argv);
		return (1);
	}
	size = 0;
	while ((*envp)[size])
		size++;
	new_envp = malloc(sizeof(char *) * (size + 2));
	if (!new_envp)
		exit(1);
	new_envp = ft_memcpy(new_envp, *envp, sizeof(char *) * (size + 2));
	free(*envp);
	*envp = new_envp;
	new_envp[size] = argv;
	new_envp[size + 1] = 0;
	return (0);
}

void	split_env(const char *string, char **variable, char **value)
{
	char	*equal;

	equal = ft_strchr(string, '=');
	if (equal)
	{
		*variable = ft_substr(string, 0, equal + 1 - string);
		*value = ft_strdup(equal + 1);
		if (!(*variable) || !(*value))
			exit(1);
	}
	else
	{
		*variable = ft_strdup(string);
		if (!(*variable))
			exit(1);
		*value = 0;
	}
}

static int	error_export(char *line)
{
	char	*variable;
	char	*value;
	char	*tmp;

	split_env(line, &variable, &value);
	if (ft_strchr(variable, '='))
	{
		tmp = variable;
		variable = ft_substr(variable, 0, ft_strchr(variable, '=') - variable);
		free(tmp);
	}
	printf("koala: export: `%s': not a valid identifier\n", variable);
	free(variable);
	if (value)
		free(value);
	return (1);
}

int	koala_export(char ***envp, char **argv)
{
	int		i;
	char	*variable;
	char	*value;
	int		ret;

	ret = 0;
	if (!argv[1])
		print_export(*envp);
	else
	{
		i = 1;
		while (argv[i])
		{
			split_env(argv[i], &variable, &value);
			if (!change_existing_env(envp, variable, value))
			{
				if (add_env(envp, ft_strdup(argv[i])))
					ret = error_export(argv[i]);
			}
			i++;
		}
	}
	return (ret);
}
