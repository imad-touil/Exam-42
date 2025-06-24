#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return i;
}

void	ft_swap(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort(char *str, int len)
{
	int	i;
	int	j;

	i = -1;
	while (++i < len - 1)
	{
		j = -1;
		while (++j < len - i -1)
		{
			if (str[j] > str[j + 1])
				ft_swap(&str[j], &str[j + 1]);
		}
	}
}

void	ft_reverse(char *str, int start, int end)
{
	while (start < end)
	{
		ft_swap(&str[start], &str[end]);
		end--;
		start++;
	}
}

int	next_permutation(char *str, int len)
{
	int	i;
	int	j;

	i = len -2;
	while (i >= 0 && str[i] >= str[i + 1])
		i--;
	if (i < 0)
		return (0);
	j = len - 1;
	while (str[j] <= str[i])
		j--;
	ft_swap(&str[i], &str[j]);
	ft_reverse(str, i + 1, len - 1);
	return (1);
}

void	ft_printstr(char *str, int len)
{
	write(1, str, len);
	write(1, "\n", 1);
}

void	ll()
{
	system("leaks -q a.out");
}

int	main(int ac, char **av)
{
	int		len;
	char	*str;

	atexit(ll);
	if (ac != 2)
		return (1);
	len = ft_strlen(av[1]);
	if (len == 1)
		return (puts(av[1]), 0);
	str = malloc(len + 1);
	if (!str)
		return (1);
	for (int i = 0; i < len; i++)
		str[i] = av[1][i];
	str[len] = '\0';
	ft_sort(str, len);
	ft_printstr(str, len);
	while (next_permutation(str, len))
		puts(str);
	// ft_printstr(str, len);
	free(str);
}
