#include "koala.h"

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
	tputs(delete_line, 1, ko_putchar);
	write(tty_fd, prompt, ft_strlen(prompt));
}

int	ko_putchar(int c)
{
	return (write(1, &c, 1));
}
