#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	set_word(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
}

void	cap(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		while (i >= 0 && str[i] <= 32)
			i--;
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		while (i >= 0 && str[i] > 32)
			i--;
	}
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
	
	write(1, "\n", 1);
}

int	main(int ac, char *av[])
{
	int	i;

	if (ac == 1)
	{
		write(1, "\n", 1);
		return (1);
	}
	i = 1;
	while (i < ac)
	{
		set_word(av[i]);
		cap(av[i]);
		ft_putstr(av[i]);
		i++;
	}
	return (0);
}