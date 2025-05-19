#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

// char	*get_line(int fd)
// {
// 	char *line;
// 	int	exit;

// 	line = malloc(99999999999);
// 	if (!line)
// 	{
// 		perror("Error");
// 		return (NULL);
// 	}
// 	exit = read(fd, line, 99999999);
// 	if (!exit)
// 	{
// 		free(line);
// 		return (NULL);
// 	}
// 	line[exit] = '\0';
// 	return (line);
// }

char	*get_line(int fd)
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

int	is_match(char *line, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		j = 0;
		while (line[i + j] == str[j] && str[j])
		{
			if (!str[j + 1])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

void	update_line(char *line, int len, int key)
{
	int	i;

	i = key;
	while (i < len + key)
	{
		line[i] = '*';
		i++;
	}
}

// void	leak()
// {
// 	system("leaks -q a.out");
// }

int	main(int ac, char **av)
{
	char	*line;
	int		len;
	int		key;
	int		i;

	// atexit(leak);
	if (ac != 2)
		return (1);
	line = get_line(0);
	len = ft_strlen(av[1]);
	while (line)
	{
		i = 0;
		while (line[i])
		{
			key = is_match((char *)line + i, av[1]);
			if (key != -1)
			{
				update_line((char *)line + i, len, key);
				i += len;
			}
			else
				i++;
		}
		printf("%s", line);
		free(line);
		line = get_line(0);
	}
}
