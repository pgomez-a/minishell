#include "../koala.h"

int	compare_env_var(char *env, char *new_env)
{
	int r;

	env = ft_strjoin(env, "=");
	new_env = ft_strjoin(new_env, "=");
	r = ft_strncmp(env, new_env, ft_strchr(new_env, '=') - new_env + 1);
	free(env);
	free(new_env);
	return (r);
}

static void	print_export_string(char **string)
{
	int		i;
	char	*variable;
	char	*value;

	i = 0;
	while (string[i])
	{
		split_env(string[i], &variable, &value);
		printf("declare -x %s", variable);
		if (ft_strchr(variable, '='))
			printf("\"%s\"", value);
		printf("\n");
		free(variable);
		if (value)
			free(value);
		i++;
	}
}

void	print_export(char **envp)
{
	int		i;
	char	*tmp;
	char	**tmp_env;

	i = -1;
	while (envp[++i]);
	tmp_env = malloc(sizeof(char *) * (i + 1));
	tmp_env = ft_memcpy(tmp_env, envp, sizeof(char *) * (i + 1));
	i = 1;
	while (tmp_env[i])
	{
		if (i > 0 && (ft_strcmp(tmp_env[i], tmp_env[i - 1]) < 0))
		{
			tmp = tmp_env[i - 1];
			tmp_env[i - 1] = tmp_env[i];
			tmp_env[i] = tmp;
			i--;
		}
		else
			i++;
	}
	print_export_string(tmp_env);
	free(tmp_env);
}
