#include <stdio.h> 
#include <ctype.h>


int main()
{
	int		a;
	int		b;
	int		c;
	char	ch;
	char	str1[100];
	char	str2[100];
	char	str3[100];

	// int ret = scanf("%d %d %d", &a, &b, &c);
	// printf("return value ==> %d, a ==> %d, b ==>> %d, c ==>> %d\n", ret, a, b, c);
	// int	ret = scanf(" ");
	// printf("return value ==> '%d', character ==> '%c'\n", ret, c);

	int	ret = scanf("%s %s %s", str1, str2, str3);
	printf("return val ==> %d, str1 ==> %s, str2 ==> %s, str3 ==> %s\n", ret, str1, str2, str3);
}
