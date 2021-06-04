#include "../koala.h"

static int	get_num_back_slash(char *beg, char *end) // Se utiliza?
{
	char	*tmp;
	int	count;

	tmp = end;
	count = 0;
	while (tmp >= beg)
	{
		if ((*tmp) != '\\')
			return (count);
		count++;
		tmp--;
	}
	return (count);
}

static void	set_quot_prompt(int tty_fd, int sin, int dob, char buff)
{
	if (buff == '\n' && sin == 1)
		write(tty_fd, "quote> ", 7);
	else if (buff == '\n' && dob == 1)
		write(tty_fd, "dquote> ", 8);
}

static void	look_quotes(int back, char buff, int *sin, int *dob)
{
	if (buff == '\"' && (*sin) == -1 && back == 0)
		(*dob) *= -1;
	else if (buff == '\'' && (*dob) == -1)
	{
		if ((back == 0 && (*sin) == -1) || (*sin) == 1)
			(*sin) *= -1;
	}
}

void	check_valid_line(t_tty_info *tty_info)
{
	int	i;
	int	sin;
	int	dob;
	int	back;

	sin = -1;
	dob = -1;
	back = 0;
	i = 0;
	while (tty_info->strings->content[i] || sin == 1 || dob == 1)
	{
		look_quotes(back, tty_info->strings->content[i], &sin, &dob);
		set_quot_prompt(STDIN_FILENO, sin, dob, tty_info->strings->content[i]);
		back = look_back_slash(tty_info->strings->content, (tty_info->strings->content) + ft_strlen(tty_info->strings->content) - 1);
		i++;
	}
}
