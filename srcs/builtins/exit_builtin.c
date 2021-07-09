#include "../../inc/koala.h"

static int	error_valid_number(int n)
{
	if (n > 255)
		n %= 256;
	return (n);
}

int	koala_exit(t_dlist *history, char **argv)
{
	int	error_status;

	error_status = 0;
	if (argv && argv[1])
	{
		error_status = ft_atoi(argv[1]);
		if (argv[2])
		{
			printf("koala: exit: too many arguments\n");
			return (1);
		}
	}
	save_history(&history);
	init_terminal(0, 2);
	if (!error_status)
		error_status = ft_atoi(get_errorvar(0, 1));
	get_errorvar(0, 0);
	if (argv && ft_strisdigit(argv[1]))
	{
		printf("koala: exit: %s: numered argument required\n", argv[1]);
		error_status = 255;
	}
	exit(error_valid_number(error_status));
	return (0);
}
