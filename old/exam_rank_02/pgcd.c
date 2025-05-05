#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char *av[])
{
	int x;
	int	y;
	int	res;

	if (ac != 3)
	{
		write(1, "\n", 1);
		return (1);
	}
	x = atoi(av[1]);
	y = atoi(av[2]);
	while (y != 0)
	{
		res = x % y;
		x = y;
		y = res;
	}
	printf("%d\n", x);
}