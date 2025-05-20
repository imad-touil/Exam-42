#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	print_board(char **board, int max_size)
{
	for (int i = 0; i < max_size; i++)
	{
		for (int j = 0; j < max_size; j++)
			printf("%c", board[i][j]);
		printf("\n");
	}
}

int	is_safe(char **board, int x, int y, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (board[x][i] == 'Q')
			return (0);
	}
	for (int i = 0; i < size; i++)
	{
		if (board[i][y] == 'Q')
			return (0);
	}
	if (!check_dig()) // TODO
		return (0);
	return (1);
}

void	n_queen(char **board, int x, int y, int size)
{
	if (x == size)
	{
		print_board(board, size); // TODO
		return ;
	}
	for (int i = 0; i < size; i++)
	{
		if (is_safe(board, i, y, size))
		{
			board[x][i] = 'Q';
			n_queen(board, x + 1, 0, size);

		}
	}
}

int	main(int ac, char **av)
{
	int		max_size;
	char	**board;

	if (ac != 2 || atoi(av[1]) <= 0)
		return (1);
	max_size = atoi(av[1]);
	board = malloc(max_size * sizeof(char *));
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
			board[i][j] = '0';
		board[i][max_size] = '\0';
	}
	n_queen(board, 0, 0, max_size);
	print_board(board, max_size);
}
