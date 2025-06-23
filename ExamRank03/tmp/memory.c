#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	int	c;

	while ((c = fgetc(f)) != EOF && isspace(c))
		;
	if (c == EOF)
		return (-1);
	ungetc(c, f);
	return 1;
}

int match_char(FILE *f, char c)
{
	int	ch;

	ch = fgetc(f);
	if (ch == EOF)
		return (-1);
	if (ch != c)
	{
		ungetc(ch, f);
		return (0);
	}
	return 1;
}

int scan_char(FILE *f, va_list ap)
{
	int	c;
	char *res = va_arg(ap, char *);

	c = fgetc(f);
	if (c == EOF)
		return (-1);
	*res = (char)c;
	return 1;
}

int scan_int(FILE *f, va_list ap)
{
	int	sign = 1;
	int	num = 0;
	int	flag = 0;
	int	*res = va_arg(ap, int *);
	int	c;

	while ((c = ))
	if (c == EOF)
		return (-1);
	if (c == '-' || c == '+')
	{
		if (c == '-')
			sign = -1;
		c = fgetc(f);
	}
	while (c != EOF && isdigit(c))
	{
		num = num * 10 + c - 48;
		flag++;
		c = fgetc(f);
	}
	if (c == EOF)
		ungetc(c, f);
	if (flag == 0)
		return (0);
	*res = num * sign;
	return 1;
}

int scan_string(FILE *f, va_list ap)
{
    int	i = 0;
	int	c;
	char	*res = va_arg(ap, char *);
	c = fgetc(f);
	if (c == EOF)
		return (-1);
	while (!isspace(c) && c != EOF)
	{
		res[i] = (char)c;
		i++;
		c = fgetc(f);
	}
	res[i] = '\0';
	if (c == EOF)
		ungetc(c, f);
	if (i == 0)
		return (1);
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
	return ret;
}