#include <stdio.h>

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

void	fill_it(char **tab, t_point size, char target, int row, int col)
{
	if (row < 0 || col < 0 || row >= size.y | col >= size.x)
		return ;

	if (tab[row][col] = 'F' || tab[row][col] != target)
		return ;
	tab[row][col] = 'F';
	fill_it(tab, size, target, row - 1, col);
	fill_it(tab, size, target, row + 1, col);
	fill_it(tab, size, target, row, col - 1);
	fill_it(tab, size, target, row, col + 1);
}

void	flood_fill(char **tab, t_point size, t_point begin)
{
	char target = tab[begin.y][begin.x];
	fill_it(tab, size, target, begin.y, begin.x);
}