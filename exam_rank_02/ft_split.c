#include <stdlib.h>
#include <stdio.h>

int	ft_strlen(const char *str)
{
	int	i;
	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	if (size == 0)
		return (len);
	i = 0;
	while (i + 1 < size && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}

int	count_word(char *str)
{
	int	i;
	int	res;
	int	key;

	res = 0;
	key = 1;
	while (str[i])
	{
		while (str[i] <= 32 && str[i])
		{
			i++;
			key = 1;
		}
		if (key && str[i])
		{
			key	= 0;
			res++;
		}
		while (str[i] > 32 && str[i])
			i++;
	}
	return (res);
}


char **ft_set_word(char **res, char *str)
{
	int	i;
	int	j;
	int	len;

	j = 0;
	i = 0;
	while (str[i])
	{
		len = 0;
		while (str[i] <= 32 && str[i])
			i++;
		while (str[i + len] && str[i + len] > 32)
			len++;
		if (len  > 0)
		{
			res[j] = malloc(sizeof(char) * (len + 1));
			if (!res[j])
				return (NULL);
			ft_strlcpy(res[j++], &str[i], len + 1);
		}
		i += len;
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split(char *str)
{
	char **res;
	int	num;

	num = count_word(str);
	res = (char **)malloc(sizeof(char *) * (num + 1));
	if (!res)
		return (NULL);
	return (ft_set_word(res, str));
}

int	main()
{
	char **test = ft_split("Hello Funny World, 1337 Is The Best\n");
	int	i = 0;
	while (i < 7)
	{
		printf("%s tot\n", test[i]);
		i++;
	}
}