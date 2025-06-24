/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:30:14 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/24 18:06:18 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	find_subset(int *set, int size, int target, int *subset, int subsize, int index)
{
	int	sum;

	if (size == index)
	{
		sum = 0;
		for (int i = 0; i < subsize; i++)
			sum += subset[i];
		if (sum == target)
		{
			for (int i = 0; i < subsize; i++)
				printf("%d ", subset[i]);
			printf("\n");
		}
		return ;
	}
	subset[subsize] = set[index];
	find_subset(set, size, target, subset, subsize + 1, index + 1);
	find_subset(set, size, target, subset, subsize, index + 1);
}

int	main(int ac, char **av)
{
	int	target;
	int	size;
	int	*set;
	int	*subset;

	if (ac < 3)
		return (1);
	target = atoi(av[1]);
	size = ac - 2;
	set = malloc(sizeof(int) * size);
	if (!set)
		return (1);
	subset = malloc(sizeof(int) * size);
	if (!subset)
		return (free(set), 1);
	for (int i = 0; i < size; i++)
		set[i] = atoi(av[i + 2]);
	find_subset(set, size, target, subset, 0, 0);
	free(subset);
	free(set);
}
