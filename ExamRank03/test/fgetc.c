#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	// FILE	*f;
	// int		c;

	// f = fopen("test.txt", "r");
	// c = fgetc(f);
	// // c = ungetc(c, f);
	// printf("%c", c);
	// // while (c != EOF)
	// // {
	// // 	printf("%c", c);
	// // 	c = fgetc(f);
	// // 	// ungetc(c, f);
	// // }

	FILE *fp = fopen("test.txt", "r");
	if (fp != NULL)
	{
		int ch = fgetc(fp);
		if (ch != EOF)
		{
			printf("Read character: %c\n", ch);
			ungetc(ch, fp); // push it back
			int ch2 = fgetc(fp);
			printf("Re-read character: %c\n", ch2);
		}
	fclose(fp);
	}

}


