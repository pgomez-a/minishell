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

void	set_prompt(t_tty_info *tty_info)
{
	char	*prompt;
	//char	*path;

	//path = getenv("PWD");
	prompt = "koala# ";
	//tputs(tgoto(cursor_address, 0, nline), 1, ko_putchar);
	tputs(carriage_return, 1, ko_putchar);
	//write(tty_fd, path, ft_strlen(path));
	//write(tty_fd, " ", 1);
	write(tty_info->tty_fd, prompt, ft_strlen(prompt));
	tty_info->xcursor = 0;
}

/**
 ** Adds a character inside the string
 **/

void	add_character(t_tty_info *tty_info, char c)
{
	char	*tmp;
	int		len;
	int		i;
	int		j;

	tmp = tty_info->string;
	len = ft_strlen(tmp) + 1;
	tty_info->string = malloc(ft_strlen(tmp) + 2);
	i = 0;
	j = 0;
	while (len)
	{
		if (i == tty_info->xcursor - 1)
			tty_info->string[i] = c;
		else
			tty_info->string[i] = tmp[j++];
		i++;
		len--;
	}
	tty_info->string[i] = 0;
	free(tmp);
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
