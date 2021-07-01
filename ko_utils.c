#include "koala.h"

/**
 ** Join the two given stings and avoid memory leaks
 **/

void	do_join(int mode, char **src, char *dst)
{
	char	*tmp;

	tmp = *src;
	(*src) = ft_strjoin(*src, dst);
	free(tmp);
	if (mode == 1)
		free(dst);
}

/**
 ** ft_putchar but for standard output fd
 **/

int	ko_putchar(int c)
{
	return (write(1, &c, 1));
}

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

int	close_quotes(int x, char *line) //preguntar pablo si se utiliza
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

/**
 ** Frees a simple char* array
 **/

void	free_split(char **split)
{
	unsigned int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	*koala_getenv(char *env_var, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!compare_env_var(envp[i], env_var))
		{
			if (ft_strchr(envp[i], '='))
				return (envp[i]);
			else
				return ("=");
		}
		i++;
	}
	return ("=");
}

char	*koala_getcwd()
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
