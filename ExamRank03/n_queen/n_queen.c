#include "n_queen.h"

void	print_board(char board[0][0], int max_size)
{
	for (int i = 0; i < max_size; i++)
	{
		for (int j = 0; j < max_size; j++)
			printf("%c", board[i][j]);
		printf("\n");
	}
}

int	main(int ac, char **av)
{
	int		max_size;

	if (ac != 2 || atoi(av[1]) <= 0)
		return (1);
	max_size = atoi(av[1]);
	char	board[max_size][max_size];
	for (int i = 0; i < max_size; i++)
	{
		for (int j = 0; j < max_size; j++)
			board[i][j] = '0';
	}
	print_board(board, max_size);
}
