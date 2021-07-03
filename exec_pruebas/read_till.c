#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char	c;

	c = 0;
	while (c != 'q')
	{
		printf("Write a character, q for exit:\n");
		scanf("%c", &c);
		printf("CHARACTER: %c\n", c);
		fflush(stdin);
	}
	return (0);
}
