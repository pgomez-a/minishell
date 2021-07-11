#include "../../inc/koala.h"

static int	error_valid_number(long long int n)
{
	if (n > 255)
		n %= 256;
	return ((int)n);
}

static int	greater_than_long(char *string, long long int *exit_status)
{
	unsigned long long int	n;
	int						negative;

	negative = 0;
	n = 0;
	if (*string == '-')
	{
		negative = 1;
		string++;
	}
	while (ft_strchr("0123456789", *string) && *string)
	{
		n = n * 10 + ((*string) - 48);
		string++;
		if ((!negative && n > __LONG_MAX__)
			|| (negative && (n - 1) > __LONG_MAX__))
			return (1);
	}
	*exit_status = n;
	if (negative)
		*exit_status *= -1;
	return (0);
}

static int	argumented_exit(char **argv, long long int *error_status)
{
	if (greater_than_long(argv[1], error_status) || (!ft_strisdigit(argv[1])
			&& (!(*argv[1] == '-' && ft_strisdigit(argv[1] + 1))))
		|| (*argv[1] == '-' && !(*(argv[1] + 1))))
	{
		printf("koala: exit: %s: numeric argument required\n", argv[1]);
		*error_status = 255;
	}
	else if (argv[2])
	{
		printf("koala: exit: too many arguments\n");
		return (1);
	}
	return (0);
}

int	koala_exit(t_dlist *history, char **argv)
{
	long long int	error_status;
	int				valid_exit;

	valid_exit = 0;
	init_terminal(0, 2);
	printf("exit\n");
	if (argv && argv[1])
		valid_exit = argumented_exit(argv, &error_status);
	else
		error_status = (unsigned int)ft_atoi(get_errorvar(0, 1));
	get_errorvar(0, 0);
	if (!valid_exit)
	{
		save_history(&history);
		exit(error_valid_number(error_status));
	}
	else
		return (1);
}
