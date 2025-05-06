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

// char	*ft_strjoin(char *s0, char *s1)
// {
// 	int	len0;
// 	int	len1;
// 	int	i;
// 	char	*res;

// 	if (!s0)
// 		return (s1);
// 	len0 = ft_strlen(s0);
// 	len1 = ft_strlen(s1);
// 	res = malloc(len0 + len1 + 1);
// 	if (!res)
// 		return (NULL);
// 	i = -1;
// 	while (s0[++i])
// 		res[i] = s0[i];
// 	i = -1;
// 	while (s1[++i])
// 	{
// 		res[len0] = s1[i];
// 		len0++;
// 	}
// 	res[len0] = '\0';
// 	return (res);
// }

char	*get_line(int fd)
{
	static char *line;
	int	exit;

	line = malloc(2);
	if (!line)
	{
		perror("Error");
		return (NULL);
	}
	exit = read(fd, line, 1024);
	if (!exit)
	{
		free(line);
		return (NULL);
	}
	return (line);
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

void	new_line(char *line, int len, int key)
{
	int	i;

	i = key;
	while (i < len + key)
	{
		line[i] = '*';
		i++;
	}
	// return (line);
}

int	main(int ac, char **av)
{
	char	*line;
	int		len;
	int		key;
	int		i;

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
				new_line((char *)line + i, len, key);
				i += len;
			}
			else
				i++;
		}
		printf("%s", line);
		line = get_line(0);
	}
}
