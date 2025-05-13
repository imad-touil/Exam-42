#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	FILE	*f;
	int		c;

	f = fopen("test.txt", "r");
	c = fgetc(f);
	c = ungetc(c, f);
	printf("%c", c);
	// while (c != EOF)
	// {
	// 	printf("%c", c);
	// 	c = fgetc(f);
	// 	// ungetc(c, f);
	// }
}