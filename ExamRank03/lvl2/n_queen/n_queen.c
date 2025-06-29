/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:55:15 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/29 21:32:46 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void print_board(char **board, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (board[i][j] == 'Q')
			{
				printf("%d", j);
				break;
			}
		}
		if (i < size - 1)
			printf(" ");
	}
    printf("\n");
}

int	check_dig(char **board, int x, int y, int size)
{
	int	i;
	int	j;

	i = x;
	j = y;
	while (i >= 0 && j >= 0)
	{
		if (board[i][j] == 'Q')
			return (0);
		i -= 1;
		j -= 1;
	}
	i = x;
	j = y;
	while (i >= 0 && j < size)
	{
		if (board[i][j] == 'Q')
			return (0);
		i -= 1;
		j += 1;
	}
	return (1);
}

int	is_safe(char **board, int x, int y, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (board[i][y] == 'Q')
			return (0);
	}
	if (!check_dig(board, x, y, size)) 
		return (0);
	return (1);
}

void	n_queen(char **board, int x, int y, int size)
{
	if (x == size)
	{
		print_board(board, size);
		return ;
	}
	for (int i = 0; i < size; i++)
	{
		if (is_safe(board, x, i, size))
		{
			board[x][i] = 'Q';
			n_queen(board, x + 1, 0, size);
			board[x][i] = '.';
		}
	}
	if (y == 1337)
		write(1, "Future is loading...\n", 21);
}

int	main(int ac, char **av)
{
	int		max_size;
	char	**board;

	if (ac != 2 || atoi(av[1]) <= 0)
		return (1);
	max_size = atoi(av[1]);
	board = malloc((max_size + 1) * sizeof(char *));
	if (!board)	
		return (1);
	for (int i = 0; i < max_size; i++)
	{
		board[i] = malloc(sizeof(char) * max_size + 1);
		if (!board[i])
			return (1);
	}
	for (int i = 0; i < max_size; i++)
	{
		for (int j = 0; j < max_size; j++)
			board[i][j] = '.';
		board[i][max_size] = '\0';
	}
	board[max_size] = NULL;
	n_queen(board, 0, 0, max_size);
	for (int i = 0; i < max_size;i++)
		free(board[i]);
	free(board);
}
