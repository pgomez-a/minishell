#include "koala.h"

/**
 ** Read user input from prompt
 **/

static void	set_quot_prompt(int tty_fd, int sin, int dob, char *buff)
{
	if (buff[0] == '\n' && sin == 1)
		write(tty_fd, "quote> ", 7);
	else if (buff[0] == '\n' && dob == 1)
		write(tty_fd, "dquote> ", 8);
}

static void	look_quotes(int back, char *buff, int *sin, int *dob)
{
	if (buff[0] == '\"' && (*sin) == -1 && back == 0)
		(*dob) *= -1;
	else if (buff[0] == '\'' && (*dob) == -1)
	{
		if ((back == 0 && (*sin) == -1) || (*sin) == 1)
			(*sin) *= -1;
	}
}

void	read_command_line(int tty_fd, char **line)
{
	char	buff[2];
	int		sin;
	int		dob;
	int		back;

	sin = -1;
	dob = -1;
	buff[1] = '\0';
	read(tty_fd, buff, 1);
	back = 0;
	while (buff[0] != '\n' || sin == 1 || dob == 1) 
	{
		do_join(line, buff);
		look_quotes(back, buff, &sin, &dob);
		set_quot_prompt(tty_fd, sin, dob, buff);
		back = look_back_slash(*line, (*line) + ft_strlen(*line) - 1);
		read(tty_fd, buff, 1);
	}
}
