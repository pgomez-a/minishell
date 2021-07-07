#include "../../inc/koala.h"

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
