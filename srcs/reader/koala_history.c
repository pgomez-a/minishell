#include "../../inc/koala.h"

t_dlist	*charge_history(void)
{
	int		fd;
	int		r;
	char	*line;
	t_dlist	*history;

	history = 0;
	fd = open("/tmp/.koala_history", O_RDONLY);
	if (fd < 0)
		return (0);
	r = get_next_line(fd, &line);
	while (r)
	{
		ft_dlstadd_front(&history, ft_dlstnew(line));
		r = get_next_line(fd, &line);
	}
	free(line);
	close(fd);
	return (history);
}

void	save_history(t_dlist **list)
{
	int		fd;
	t_dlist	*tmp_list;

	fd = open("/tmp/.koala_history", O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd < 0)
		exit(2);
	tmp_list = *list;
	*list = ft_dlstlast(*list);
	while (*list)
	{
		write(fd, (*list)->content, ft_strlen((*list)->content));
		write(fd, "\n", 1);
		*list = (*list)->previous;
	}
	close(fd);
	*list = tmp_list;
	ft_dlstclear(list, free);
}

void	put_history(t_tty_info *tty_info, char n)
{
	unsigned int	len;

	len = ft_strlen(tty_info->strings->content);
	if (n == 'A' && tty_info->strings->next)
	{
		while (len--)
		{
			tputs(cursor_left, 1, ko_putchar);
			tputs(delete_character, 1, ko_putchar);
		}
		tty_info->strings = tty_info->strings->next;
		tputs(tty_info->strings->content, 1, ko_putchar);
		tty_info->xcursor = ft_strlen(tty_info->strings->content);
	}
	else if (n == 'B' && tty_info->strings->previous)
	{
		while (len--)
		{
			tputs(cursor_left, 1, ko_putchar);
			tputs(delete_character, 1, ko_putchar);
		}
		tty_info->strings = tty_info->strings->previous;
		tputs(tty_info->strings->content, 1, ko_putchar);
		tty_info->xcursor = ft_strlen(tty_info->strings->content);
	}
}
