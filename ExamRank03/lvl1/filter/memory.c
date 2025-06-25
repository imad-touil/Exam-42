#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int	handel_error()
{
	perror("error");
	return (1);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*get_line(int fd)
{
	int		byte;
	int		i;
	char	c;
	char	*str;

	str = malloc(2147483);
	if (!str)
		return (NULL);
	byte = read(fd, &c, 1);
	i = 0;
	while (byte > 0)
	{
		str[i] = c;
		if (memmem(str, i, "\n\0", strlen("\n\0")))
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

void	filter(char *line, char *filter)
{
	char	*found = memmem(line, ft_strlen(line), filter, ft_strlen(filter));
	int		len;

	found = memmem(line, ft_strlen(line), filter, ft_strlen(filter));
	while (found)
	{
		len = ft_strlen(filter);
		for (int i = 0; i < ft_strlen(filter); i++)
			found[i] = '*';
		found = memmem(found + len, ft_strlen(line + len),
			filter, ft_strlen(filter));
		
	}
}

int	main(int ac, char **av)
{
	char	*line;

	if (ac != 2)
		return (1);
	line = get_line(0);
	while (line)
	{
		filter(line, av[1]);
		printf("%s", line);
		free(line);
		line = get_line(0);
	}
}