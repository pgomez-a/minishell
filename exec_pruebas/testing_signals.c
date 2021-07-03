#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int	main(void)
{
	printf("Aqui comienza.\n");
	if (fork() > 0)
	{
		printf("Soy el papi, estoy esperando...\n");
		wait(NULL);
	}
	else
	{
		printf("Soy el hijo comienzo a hacer cositas\n");
		while (1)
			printf("AAAA");
		exit(0);
	}
	printf("Fin.\n");
}
