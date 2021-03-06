#include "../inc/koala.h"

/**
 ** Sets terminal in read_mode(1) for reading the input form the client
 ** exec-output_mode(2) for for the ecution of commands
 ** or resets the terminal to its original status(3)
 ** When tty_mode value is NULL, inits the main structure and charge the
 ** command history
 **/

t_tty_info	*init_terminal(t_tty_info *tty_info, int tty_mode)
{
	static struct termios	original_tty_settings;

	if (tty_mode == 1)
		tcsetattr(STDIN_FILENO, TCSANOW, &tty_info->read_tty_settings);
	else if (tty_mode == 2)
		tcsetattr(STDIN_FILENO, TCSANOW, &original_tty_settings);
	else
	{
		tty_info = ft_calloc(1, sizeof(t_tty_info));
		tcgetattr(STDIN_FILENO, &original_tty_settings);
		tgetent(0, getenv("TERM"));
		ft_memcpy(&tty_info->read_tty_settings,
			&original_tty_settings, sizeof(struct termios));
		tty_info->read_tty_settings.c_iflag &= ~(IXON);
		tty_info->read_tty_settings.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
		tty_info->read_tty_settings.c_oflag &= ~(OPOST);
		tty_info->history = charge_history();
	}
	return (tty_info);
}

/**
 ** Writes koala's prompt
 **/

void	set_prompt(void)
{
	char	*prompt;

	prompt = "koala# ";
	tputs(enter_bold_mode, 1, ko_putchar);
	write(STDIN_FILENO, prompt, ft_strlen(prompt));
	tputs(exit_attribute_mode, 1, ko_putchar);
}

/**
 ** Charges env variables into a char * array
 **/

static char	**alloc_envp(char	**envp)
{
	int		size;
	char	**new_envp;

	size = 0;
	while (envp[size])
		size++;
	new_envp = malloc(sizeof(char *) * (size + 1));
	if (!new_envp)
		exit(1);
	size = 0;
	while (envp[size])
	{
		new_envp[size] = ft_strdup(envp[size]);
		if (!new_envp[size])
			exit(1);
		size++;
	}
	new_envp[size] = 0;
	return (new_envp);
}

/**
 ** Draw banner with koala
 **/

static void	draw_koala(void)
{
	ft_printf("\033[38;5;40m");
	ft_printf("      ___           ___           ___                         ___      \n");
	ft_printf("     /__/|         /  /\\         /  /\\                       /  /\\     \n");
	ft_printf("\033[38;5;41m");
	ft_printf("    |  |:|        /  /::\\       /  /::\\                     /  /::\\    \n");
	ft_printf("    |  |:|       /  /:/\\:\\     /  /:/\\:\\    ___     ___    /  /:/\\:\\   \n");
	ft_printf("\033[38;5;42m");
	ft_printf("  __|  |:|      /  /:/  \\:\\   /  /:/~/::\\  /__/\\   /  /\\  /  /:/~/::\\  \n");
	ft_printf(" /__/\\_|:|____ /__/:/ \\__\\:\\ /__/:/ /:/\\:\\ \\  \\:\\ /  /:/ /__/:/ /:/\\:\\ \n");
	ft_printf("\033[38;5;43m");
	ft_printf(" \\  \\:\\/:::::/ \\  \\:\\ /  /:/ \\  \\:\\/:/__\\/  \\  \\:\\  /:/  \\  \\:\\/:/__\\/ \n");
	ft_printf("  \\  \\::/~~~~   \\  \\:\\  /:/   \\  \\::/        \\  \\:\\/:/    \\  \\::/      \n");
	ft_printf("\033[38;5;44m");
	ft_printf("   \\  \\:\\        \\  \\:\\/:/     \\  \\:\\         \\  \\::/      \\  \\:\\      \n");
	ft_printf("    \\  \\:\\        \\  \\::/       \\  \\:\\         \\__\\/        \\  \\:\\     \n");
	ft_printf("\033[38;5;45m");
	ft_printf("     \\__\\/         \\__\\/         \\__\\/                       \\__\\/     \n");
	ft_printf("\n");
	ft_printf("\033[39m");
}

int	main(int argc, char *argv[], char *envp[])
{
	t_tty_info		*tty_info;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Not valid arguments\n");
		return (1);
	}
	signal(SIGILL, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	tty_info = 0;
	tty_info = init_terminal(tty_info, 0);
	envp = alloc_envp(envp);
	draw_koala();
	while (1)
	{
		set_prompt();
		if (!read_command_line(tty_info))
			man_command_line(tty_info->history, &envp);
	}
	return (0);
}
