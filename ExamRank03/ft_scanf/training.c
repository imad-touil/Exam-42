/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 22:56:29 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/10 02:14:06 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

int match_space(FILE *f)
{
        // Some code here
	int	ch;

	ch = fgetc(f);
	while (ch != EOF && isspace(ch))
		ch = fgetc(f);
	if (ch == EOF)
		return (-1);
	ungetc(ch, f);
	return 1;
}

int match_char(FILE *f, char c)
{
        // Some code here
	int	ch;

	ch = fgetc(f);
	if (ch == EOF)
		return (-1);
	if (ch != c)
		return (ungetc(ch, f), 0);
	return 1;
}

int scan_char(FILE *f, va_list ap)
{
        // Some code here
	int ch;

	ch = fgetc(f);
	if (ch == EOF)
		return (-1);
	*va_arg(ap, char *) = (char)ch;
	return 1;
}

int scan_int(FILE *f, va_list ap)
{
        // Some code here
	int	*res;
	int	ch;
	int	i;
	int	num;
	int	sign;
	
	sign = 1;
	i = 0;
	num = 0;
	ch = fgetc(f);
	res = va_arg(ap, int *);
	if (ch == '-' || ch == '+')
	{
		if (ch == '-')
			sign = -1;
		ch = fgetc(f);
	}
	while (isdigit(ch) && ch != EOF)
	{
		num = num * 10 + ch - 48;
		ch = fgetc(f);
		i++;
	}
	if (ch != EOF)
		ungetc(ch, f);
	if (i == 0)
		return (0);
	*res = num * sign;
	return 1;
}

int scan_string(FILE *f, va_list ap)
{
    // Some code here
	int	i;
	int	ch;
	char	*res;

	i = 0;
	res = va_arg(ap, char *);
	ch = fgetc(f);
	if (ch == EOF)
		return (-1);
	while (ch != EOF && !isspace(ch))
		res[i++] = ch;
	if (ch != EOF)
		ungetc(ch, f);
	if (i == 0)
		return (0);
	res[i] = '\0';
	return 1;
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return (ret);
}

int	main(void)
{
	int	ret;
	int d1;
	int d2;

	ret = ft_scanf("%d %d", &d1, &d2 );
	printf("this is the character %d, %d && this is the return value %d\n", d1, d2, ret);
}