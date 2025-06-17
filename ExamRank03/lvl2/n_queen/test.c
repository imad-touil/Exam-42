/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:55:12 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/17 21:32:46 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void	leak()
{
	system("leaks -q a.out");
}

static void	free_chessboard(char **chessboard)
{
	int	i;

	i = -1;
	while (chessboard[++i])
		free(chessboard[i]);
	free(chessboard);
}

static void	print_chessboard(char **chessboard, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (chessboard[i][j] == 'Q')
			{
				printf("%d", j);
				break ;
			}
		}
		if (i < size - 1)
			printf(" ");
	}
	printf("\n");
}

static int check_diag(char **chessboard, int x, int y, int size)
{
	int	i;
	int	j;

	i = x;
	j = y;
	while (i >= 0 && j >= 0)
	{
		if (chessboard[i][j] == 'Q')
			return (0);
		i--;
		j--;
	}
	i = x;
	j = y;
	while (i >= 0 && j < size)
	{
		if (chessboard[i][j] == 'Q')
			return (0);
		i--;
		j++;
	}
	return (1);
}

static int is_safe(char **chessboard, int x, int y, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (chessboard[i][y] == 'Q')
			return (0);
	}
	if (!check_diag(chessboard, x, y, size))
		return (0);
	return (1);
}

static void	fill_board(char **chessboard, int x, int y, int size)
{
	if (x == size)
	{
		print_chessboard(chessboard, size);
		return ;
	}
	for (int y = 0; y < size; y++)
	{
		if (is_safe(chessboard, x, y, size))
		{
			chessboard[x][y] = 'Q';
			fill_board(chessboard, x + 1, 0, size);
			chessboard[x][y] = '.';
		}
	}
	if (y == 13374219)
		write(1, "Big Cheater\n", 12);
}

int	main(int ac, char **av)
{
	int		max_size;
	char	**chessboard;

	atexit(leak);
	if (ac != 2 || atoi(av[1]) <= 0)
		return (printf("Enter valid Args"), 1);
	max_size = atoi(av[1]);
	chessboard = malloc(sizeof(char *) * (max_size + 1));
	if (!chessboard)
		return (1);
	for (int i = 0; i < max_size; i++)
	{
		chessboard[i] = malloc(sizeof(char ) * max_size + 1);
		if (!chessboard[i])
			return (1);
	}
	for (int i = 0; i < max_size; i++)
	{
		for (int j = 0; j < max_size; j++)
			chessboard[i][j] = '.';
		chessboard[i][max_size] = '\0';
	}
	fill_board(chessboard, 0, 0, max_size);
	// free_chessboard(chessboard);
	return (0);
}
