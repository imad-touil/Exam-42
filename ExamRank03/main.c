#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(int ac, char **av)
{
	char *str;

	if(ac != 2)
	{
		printf("Enter valid Args\n");
		return (1);
	}
	str = av[1];
	if (!strcmp(av[1], "n_queen"))
	{
		system("cc -Wall -Wextra -Werror n_queen/n_queen.c");
		system("./a.out 8");
	}
	else if (!strcmp(av[1], "filter"))
	{
		system("cc -Wall -Wextra -Werror filter/filter.c");
		system("./a.out Hi");
	}
	else if (!strcmp(av[1], "get_next_line"))
	{
		system("cc -Wall -Wextra -Werror get_next_line/get_next_line.c");
		system("./a.out");
	}
	else if (!strcmp(av[1], "ft_scanf"))
	{
		system("cc -Wall -Wextra -Werror ft_scanf/ft_scanf.c");
		system("./a.out");
	}
	else
		printf("Enter valid Args\n");
	return (0);
}