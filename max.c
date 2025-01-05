int	max(int* tab, unsigned int len)
{
	int	max;
	int	i;

	i = 1;
	max = tab[0];
	while (i < len)
	{
		if (tab[i] > max)
			max = tab[i];
		i++;
	}
	return (max);
}
