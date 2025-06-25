/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:58:40 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/24 22:12:16 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void	filter(char *str, char *filter)
{
	char *found = memmem(str, strlen(str), filter, strlen(filter));
	while(found)
	{
		int len = strlen(filter);
		for(int i = 0;i < len;i++)
			found[i] = '*';
		found = memmem(found + len, strlen(found + len), filter, strlen(filter));
	}
}

char *get_next_line(int fd)
{
	int	i = 0;
	int j = 0;
	char c;
	char *buffer = malloc(999999999);
	if (!buffer)
		return NULL;
	j = read(fd,&c,1);
	if (j < 0)
	{
		perror("Error");
		return NULL;
	}
	while (j)
	{
		buffer[i] = c;
		i++;
		if (memmem(buffer, i, "\n\0", strlen("\n\0")))
			break ;
		j = read(fd,&c,1);
	}
	if (!j)
		return NULL;
	return buffer;
}

void	ff()
{
	system("leaks -q a.out");
}

int main(int ac,char **av)
{
	atexit(ff);
	if (ac != 2)
		return 1;
	char *str = get_next_line(0);
	while(str)
	{
		filter(str,av[1]);
		fprintf(stdout,"%s",str);
		free(str);
		str = get_next_line(0);
	}
}