#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <termios.h>

void	hola_que_ase()
{
	printf("esta es la funcion de señal\n");
	exit(0);
}

int	main(void)
{
	pid_t kid;
	int	count = 10;
	struct termios tty_info;

	tcgetattr(STDIN_FILENO, &tty_info);
	tty_info.c_lflag &= ~ISIG;
	tcsetattr(STDIN_FILENO, TCSANOW, &tty_info);
	kid = 0;
	printf("Aqui comienza.\n");
	kid = fork();
	if (kid > 0)
	{
		printf("Soy el papi, estoy esperando...\n");
		while (count--)
			printf("waiting...\n");
		wait(NULL);
	}
	else
	{
		if (signal(SIGINT, hola_que_ase) != SIG_IGN)
		{
		printf("Soy el hijo comienzo a hacer cositas\n");
		while (1)
			write(1, "A", 1);
		exit(0);
		}
		else
			printf("a ver como fnsiona\n");
	}
	printf("Fin.\n");
}
