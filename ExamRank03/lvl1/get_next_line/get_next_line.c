#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char	*get_next_line(int fd)
{
	int		byte;
	int		i;
	char	c;
	char	*str;

	str = malloc(999999999999);
	if (!str)
		return (NULL);
	byte = read(fd, &c, 1);
	i = 0;
	while (byte > 0)
	{
		str[i] = c;
		if (c == '\n' || c == EOF)
			break ;
		i++;
		byte = read(fd, &c, 1);
	}
	if (i == 0 || byte < 0)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("test.txt", O_RDWR, O_CREAT, 0777);
	str	= get_next_line(fd);
	while (str)
	{
		printf("%s", str);
		str	= get_next_line(fd);
	}
	return (0);
}