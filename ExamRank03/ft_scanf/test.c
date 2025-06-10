#include <stdio.h>


int	main(void)
{
	int	ret;
	int d1;
	int d2;

	ret = scanf("%d %d", &d1, &d2 );
	printf("this is the character %d, %d && this is the return value %d\n", d1, d2, ret);
}