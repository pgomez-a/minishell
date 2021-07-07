#include "../../inc/koala.h"

int	redirect_inp(t_que *red)
{
	int	file;

	file = open(red->line, O_RDONLY, 0777);
	if (file < 0)
	{
		printf("koala: no such file or directory: %s\n", red->line);
		return (-1);
	}
	dup2(file, STDIN_FILENO);
	close(file);
	return (0);
}

int	redirect_add(t_que *red)
{
	int	file;

	file = open(red->line, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (file < 0)
	{
		printf("koala: can't operate with %s\n", red->line);
		return (-1);
	}
	dup2(file, STDOUT_FILENO);
	dup2(file, STDERR_FILENO);
	close(file);
	return (0);
}

int	redirect_app(t_que *red)
{
	int	file;

	file = open(red->line, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (file < 0)
	{
		printf("koala: can't operate with %s\n", red->line);
		return (-1);
	}
	dup2(file, STDOUT_FILENO);
	dup2(file, STDERR_FILENO);
	close(file);
	return (0);
}

static void	launch_prompt(int std_in, int file, t_que *red)
{
	char	*line;

	while (1)
	{
		write(std_in, "> ", 2);
		get_next_line(std_in, &line);
		if (!ft_strcmp(line, red->line))
		{
			free(line);
			break ;
		}
		write(file, line, ft_strlen(line));
		write(file, "\n", 1);
		free(line);
	}
}

int	redirect_rdin(int std_in, t_que *red)
{
	int		file;

	file = open("/tmp/.koala_heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	launch_prompt(std_in, file, red);
	close(file);
	file = open("/tmp/.koala_heredoc", O_RDONLY, 0777);
	if (file < 0)
	{
		printf("koala: no such file or directory: %s\n", red->line);
		return (-1);
	}
	dup2(file, STDIN_FILENO);
	close(file);
	return (0);
}
