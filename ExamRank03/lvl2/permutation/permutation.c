/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 02:07:09 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/23 02:56:00 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	swap(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort(char *str, int len)
{
	char c;
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if (str[j] > str[j + 1])
				swap(&str[j], &str[j + 1]);
		}
	}
}

void	print_per(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(1, str, len);
	write(1, "\n", 1);
}

int	is_used(char *str, int start, int current)
{
	for (int i = start; i < current; i++)
	{
		if (str[i] == str[current])
			return (1);
	}
	return (0);
}

void	permut(char *str, int start, int end)
{
	if (start == end)
		print_per(str);
	else
	{
		for (int i = start; i <= end; i++)
		{
			if (is_used(str, start, i))
				continue ;
			swap(&str[start], &str[i]);
			permut(str, start + 1, end);
			swap(&str[start], &str[i]);
		}
		
	}
}

int	main(int ac, char **av)
{
	int	len;
	char *str;

	if (ac != 2)
		return (1);
	len = ft_strlen(av[1]);
	str = malloc(len + 1);
	if (!str)
		return (1);
	for (int i = 0; i < len; i++)
		str[i] = av[1][i];
	str[len] = '\0';
	sort(str, len);
	permut(str, 0, len - 1);
	free(str);
	
}

