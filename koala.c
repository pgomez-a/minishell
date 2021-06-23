#include "koala.h"

/**
 ** Sets terminal in read_mode(1) for reading the input form the client
 ** exec-output_mode(2) for for the ecution of commands
 ** or resets the terminal to its original status(3)
 ** When tty_mode value is NULL, inits the main structure and charge the command history
 **/

t_tty_info	*init_terminal(t_tty_info *tty_info, int tty_mode)
{
	static struct termios	original_tty_settings;

	if (tty_mode == 2)
		tcsetattr(STDIN_FILENO, TCSANOW, &tty_info->output_tty_settings);
	else if (tty_mode == 1)
		tcsetattr(STDIN_FILENO, TCSANOW, &tty_info->read_tty_settings);
	else if (tty_mode == 3)
		tcsetattr(STDIN_FILENO, TCSANOW, &original_tty_settings);
	else
	{
		tty_info = ft_calloc(1, sizeof(t_tty_info));
		tcgetattr(STDIN_FILENO, &original_tty_settings);
		tgetent(0, getenv("TERM"));
		ft_memcpy(&tty_info->read_tty_settings, &original_tty_settings, sizeof(struct termios));
		tty_info->read_tty_settings.c_iflag &= ~(IXON);
		tty_info->read_tty_settings.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
		tty_info->read_tty_settings.c_oflag &= ~(OPOST);
		ft_memcpy(&tty_info->output_tty_settings, &original_tty_settings, sizeof(struct termios));
		tty_info->output_tty_settings.c_lflag &= ~ISIG;
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
	tputs(delete_line, 1, ko_putchar);
	write(STDIN_FILENO, prompt, ft_strlen(prompt));
}

int	main(void)
{
	t_tty_info		*tty_info;

	tty_info = 0;
	tty_info = init_terminal(tty_info, 0);
	while (1)
	{
		set_prompt();
		read_command_line(tty_info);
		if (tty_info->history->content && *(tty_info->history->content) == 'q') // salida temporal para probar hasta tener el builtin de exit
		{
			save_history(&tty_info->history);
			init_terminal(tty_info, 3);
			free(tty_info);
			return (0);
		}
		man_command_line(tty_info->history->content);
	}
	return (0);
}
