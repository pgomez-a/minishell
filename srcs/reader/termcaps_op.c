#include "../../inc/koala.h"

/**
 ** Moves the cursor or calls history commands
 **/

int	arrow_functions(t_tty_info *tty_info, char n)
{
	if (n == 'C' && tty_info->xcursor != ft_strlen(tty_info->strings->content))
	{
		tputs(cursor_right, 1, ko_putchar);
		tty_info->xcursor++;
		return (1);
	}
	else if (n == 'D' && tty_info->xcursor != 0)
	{
		tputs(cursor_left, 1, ko_putchar);
		tty_info->xcursor--;
		return (1);
	}
	else if (n == 'A' || n == 'B')
		put_history(tty_info, n);
	return (0);
}

/**
 ** Cleans buffer, and returns break
 **/

char	reset_line_tc(t_tty_info *tty_info)
{
	if (tty_info->strings->content)
	{
		free(tty_info->strings->content);
		tty_info->strings->content = ft_strdup("");
	}
	return ('\n');
}

/**
 ** Deletes a character from buffer and output where the cursor is placed
 **/

char	delete_tc(t_tty_info *tty_info)
{
	char	*tmp;

	if (arrow_functions(tty_info, 'D'))
	{
		tmp = tty_info->strings->content;
		tty_info->strings->content = ko_delete_ch(tmp, tty_info->xcursor);
		free(tmp);
		tputs(delete_character, 1, ko_putchar);
	}
	return (0);
}
