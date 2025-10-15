#include <stdlib.h>
#include <stdio.h>

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

int	check_diag(char **chess_board, int x, int y, int size)
{
	int	i;
	int	j;

	i = x;
	j = y;
	while (i >= 0 && j >= 0)
	{
		if (chess_board[i][j] == 'Q')
			return (0);
		i -= 1;
		j -= 1;
	}
	i = x;
	j = y;
	while (i >= 0 && j < size)
	{
		if (chess_board[i][j] == 'Q')
			return (0);
		i -= 1;
		j += 1;
	}
	return (1);
}

int	is_safe(char **chess_board, int x, int y, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (chess_board[i][y] == 'Q')
			return (0);
	}
	if (!check_diag(chess_board, x, y, size))
		return (0);
	return (1);
}

void	nqueen(char **chess_board, int x, int y, int size)
{
	if (x == size)
	{
		print_board(chess_board, size); // TODO
		return ;
	}
	for (int i = 0; i < size; i++)
	{
		if (is_safe(chess_board, x, i, size))
		{
			chess_board[x][i] = 'Q';
			nqueen(chess_board, x + 1, 0, size);
			chess_board[x][i] = '.';
		}
	}
}

int	main(int ac, char **av)
{
	char	**chess_board;
	int		max_size;

	if (ac != 2 || atoi(av[1]) <= 0)
		return (printf("Enter Valid Args!"), 1);
	max_size = atoi(av[1]);
	chess_board = malloc(sizeof(char *) * (max_size + 1));
	if (!chess_board)
		return (perror("|"), 1);
	for (int i = 0; i < max_size; i++)
	{
		chess_board[i] = malloc(max_size + 1);
		if (!chess_board)
			return (perror("|"), 1);
	}
	for (int i = 0; i < max_size; i++)
	{
		for (int j = 0; j < max_size; j++)
			chess_board[i][j] = '.';
		chess_board[i][max_size] = '\0';
	}
	chess_board[max_size] = NULL;
	nqueen(chess_board, 0, 0, max_size);
}
