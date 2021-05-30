#include "koala.h"

/**
 ** Check if the current character is affected by backslash or not
 **/

int	look_back_slash(char *beg, char *end)
{
	char	*tmp;
	int		count;

	tmp = end;
	count = 0;
	while (tmp >= beg)
	{
		if ((*tmp) != '\\')
			return (count % 2);
		count++;
		tmp--;
	}
	return (count % 2);
}

/**
 ** Join the two given stings and avoid memory leaks
 **/

void	do_join(char **src, char *dst)
{
	char	*tmp;

	tmp = *src;
	(*src) = ft_strjoin(*src, dst);
	free(tmp);
}

/**
 ** Write koala prompt
 **/

void	set_prompt(int tty_fd)
{
	char	*prompt;

	prompt = "koala# ";
	write(tty_fd, prompt, ft_strlen(prompt));
}
