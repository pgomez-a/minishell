#include "koala.h"

/**
 ** Read user input from prompt
 **/

void	read_command_line(int tty_fd, char **line)
{
	char	buff[2];

	buff[1] = '\0';
	read(tty_fd, buff, 1);
	while (buff[0] != '\n')
	{
		do_join(0, line, buff);
		read(tty_fd, buff, 1);
	}
}
