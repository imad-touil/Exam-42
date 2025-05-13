#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	MAX_SIZE = 20;

// char	**create_board(int size)
// {
// 	char **board = malloc(sizeof(char*) * size);
// 	size_t i = 0;
// 	while (i < size)
// 	{
// 		board[i] = malloc(sizeof(char) * size + 1);
// 		for (int j = 0; j < size; j++)
// 		{
// 			board[i][j] = '0';
// 		}
// 		board[i][size] = '\0';
// 		i++;
// 	}
// 	board[i] = NULL;
// 	return board;
// }

void print_board(char board[MAX_SIZE][MAX_SIZE], int size, int i)
{
	if (!i)
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
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				printf("%c",board[i][j]);
			printf("\n");
		}
	}
    printf("\n");
}

int	check_di(char board[MAX_SIZE][MAX_SIZE], int aard,int toul,int size)
{
	for (int i = 1; i < size; i++)
	{
		if (aard + i >= size || toul + i >= size)
			break;
		if (board[toul + i][aard + i] == 'Q')
			return (0);
	}
	for (int i = 1; i < size; i++)
	{
		if (aard - i < 0 || toul - i < 0)
			break;
		if (board[toul - i][aard - i] == 'Q')
			return (0);
	}
	for (int i = 1; i < size; i++)
	{
		if (aard + i >= size || toul - i < 0)
			break;
		if (board[toul - i][aard + i] == 'Q')
			return (0);
	}
	for (int i = 1; i < size; i++)
	{
		if (aard - i < 0 || toul + i >= size)
			break;
		if (board[toul + i][aard - i] == 'Q')
			return (0);
	}
	return (1);
}

int	is_safe(char board[MAX_SIZE][MAX_SIZE], int aard,int toul,int size)
{
	for (int i = 0; i < size; i++)
	{
		if (board[toul][i] == 'Q')
			return (0);
	}
	for (int i = 0; i < size; i++)
	{
		if (board[i][aard] == 'Q')
			return (0);
	}
	if (!check_di(board, aard,toul,size))
		return (0);
	return (1);
}

void	n_quein(char board[MAX_SIZE][MAX_SIZE],int aard ,int toul, int size)
{
	if (toul == size)
	{
		print_board(board, size, 0);
		// print_board(board, size, 1);
		return ;
	}
	for (size_t i = 0; i < size; i++)
	{
		if (is_safe(board,i,toul,size))
		{
			board[toul][i] = 'Q';
			n_quein(board, 0, toul + 1,size);
			board[toul][i] = '0';
		}
	}
}

int	main(int ac,char **av)
{
	if (ac != 2 || atoi(av[1]) <= 0)
		return (1);
	MAX_SIZE = atoi(av[1]);
	char board[MAX_SIZE][MAX_SIZE];
	for (size_t i = 0; i < MAX_SIZE; i++)
	{
		for (size_t j = 0; j < MAX_SIZE; j++)
			board[i][j] = '0';
	}
	n_quein(board,0,0,MAX_SIZE);
}