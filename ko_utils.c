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
