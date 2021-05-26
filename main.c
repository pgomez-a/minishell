#include "prompt.h"

static void	check_command_line(char *str)
{
	t_cmd	elem;
	char	**div;
	int	error;
	int	x;

	x = 0;
	div = ft_split(str, ';');
	while (div[x])
	{
		init_queue(div[x]);
		elem.tot = ft_strtrim(div[x], " ");
		error = set_command(elem.tot, &elem);
		clear_cmand_struct(&elem);
		free(div[x]);
		if (error)
			break;
		x++;
	}
	if (!error)
		ft_printf("Ejecutar comandos cola\n");;
	free(div);
}

int	main(void)
{
	char	buffer[2];
	char	*str;
	char	*tmp;

	buffer[1] = '\0';
	while (1)
	{
		str = ft_strdup("");
		write(1, "# ", 2);
		read(1, buffer, 1);
		while (buffer[0] != '\n')
		{
			tmp = str;
			str = ft_strjoin(str, buffer);
			free(tmp);
			read(1, buffer, 1);
		}
		check_command_line(str);
		free(str);
	}
}
