#include "../../inc/koala.h"

/**
 ** Deletes the d positoned character in the string
 **/

char	*ko_delete_ch(const char *str, int d)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(ft_strlen(str));
	while (str[i])
	{
		if (i != d)
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = 0;
	return (new_str);
}

/**
 ** Check if there are close quotes or not
 **/

int	close_quotes(int x, char *line)
{
	char	quot;

	quot = line[x++];
	while (line[x])
	{
		if (line[x] == quot)
			return (1);
		x++;
	}
	return (0);
}

char	*get_errorvar(int exit_status, int ret)
{
	static char	*error = 0;

	if (ret)
	{
		if (error)
			return (error);
		else
			return ("0");
	}
	if (error)
		free(error);
	if (exit_status)
		error = ft_itoa(exit_status);
	else
		error = 0;
	return (0);
}

char	*koala_getenv(char *env_var, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strcmp(env_var, "?"))
			return (get_errorvar(0, 1));
		if (!compare_env_var(envp[i], env_var))
		{
			if (ft_strchr(envp[i], '='))
				return (ft_strchr(envp[i], '=') + 1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

char	*koala_getcwd(void)
{
	int		size;
	char	*string;

	size = 10;
	string = malloc(sizeof(char) * 16);
	while (!getcwd(string, size))
	{
		free(string);
		size *= 2;
		string = malloc(sizeof(char) * size);
	}
	return (string);
}
