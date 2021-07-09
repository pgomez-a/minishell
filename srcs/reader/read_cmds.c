#include "../../inc/koala.h"

/**
 ** Adds a character inside the string
 **/

void	add_character(t_tty_info *tty_info, char c)
{
	char			*tmp;
	int				len;
	unsigned int	i;
	unsigned int	j;

	tmp = tty_info->strings->content;
	len = ft_strlen(tmp) + 1;
	tty_info->strings->content = malloc(ft_strlen(tmp) + 2);
	if (!(tty_info->strings->content))
		exit(1);
	i = 0;
	j = 0;
	while (len)
	{
		if (i == tty_info->xcursor - 1)
			tty_info->strings->content[i] = c;
		else
			tty_info->strings->content[i] = tmp[j++];
		i++;
		len--;
	}
	tty_info->strings->content[i] = 0;
	free(tmp);
}

/**
 ** Reads from STDIN_FILENO each character
 **/

static char	read_fromtty(t_tty_info *tty_info)
{
	char	buff;

	read(STDIN_FILENO, &buff, 1);
	if (!ft_isprint(buff) && buff != '\n')
	{
		if (buff == 3)
			return (reset_line_tc(tty_info));
		if (buff == 4 && tty_info->xcursor == 0)
			koala_exit(tty_info->history, 0);
		if (buff == 127)
			return (delete_tc(tty_info));
		if (buff == 27)
		{
			read(STDIN_FILENO, &buff, 1);
			read(STDIN_FILENO, &buff, 1);
			if (buff == 'C' || buff == 'D' || buff == 'A' || buff == 'B')
				arrow_functions(tty_info, buff);
		}
		return (0);
	}
	tty_info->xcursor++;
	return (buff);
}

/**
 ** Charge characters in the output string and in the buffer,
 ** stops when lines breaks
 **/

void	read_line(t_tty_info *tty_info)
{
	char	buff[2];

	buff[1] = 0;
	buff[0] = read_fromtty(tty_info);
	while (buff[0] != '\n')
	{
		if (buff[0])
		{
			add_character(tty_info, buff[0]);
			tputs(enter_insert_mode, 1, ko_putchar);
			tputs(buff, 1, ko_putchar);
			tputs(exit_insert_mode, 1, ko_putchar);
		}
		buff[0] = read_fromtty(tty_info);
	}
}

/**
 ** Sets non_canonical mode, and charge the command line
 **/

int	read_command_line(t_tty_info *tty_info)
{
	int	r;

	r = 1;
	tty_info->xcursor = 0;
	tty_info->strings = ft_dlstmap(tty_info->history, ft_strdup, free);
	ft_dlstadd_front(&tty_info->strings, ft_dlstnew(ft_strdup("")));
	init_terminal(tty_info, 1);
	read_line(tty_info);
	if ((tty_info->strings->content)[0])
	{
		ft_dlstadd_front(&tty_info->history,
			ft_dlstnew(ft_strdup(tty_info->strings->content)));
		r = 0;
	}
	init_terminal(tty_info, 2);
	ft_dlstclear(&tty_info->strings, free);
	tputs("\n", 1, ko_putchar);
	tputs(carriage_return, 1, ko_putchar);
	return (r);
}
