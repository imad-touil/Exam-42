int swiitch(int nbr)
{
	return (nbr >> 4 | nbr << 4);
}

int	main()
{
	printf("%d\n", swiitch(5));
}