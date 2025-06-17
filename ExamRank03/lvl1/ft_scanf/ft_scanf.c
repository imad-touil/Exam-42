#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c;
	c = fgetc(f);
	if (c == EOF)
		return -1;
	if (!isspace(c))
		return ungetc(c, f), 1;
	while ((c = fgetc(f)) != EOF && isspace(c))
		;
	if (c != EOF)
		ungetc(c, f);
    return (1);
}

int match_char(FILE *f, char x)
{
	int c;
	c = fgetc(f);
	if (c == EOF)
		return -1;
	if (x != c)
	{
		ungetc(c, f);
		return -1;
	}
	if (x == c)
		return 1;
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
	char c;
	c = fgetc(f);
	if (c == EOF)
		return -1;
	char *x = va_arg(ap, char *);
	*x = c;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
	int c;
	int res = 0;
	int sign = 1;
	int flag = 0;

	c = fgetc(f);
	if (c == EOF)
		return -1;
	if (c == '-' || c == '+')
	{
		if (c == '-')
			sign = -1;
		c = fgetc(f);
	}
	while (c != EOF && isdigit(c))
	{
		flag++;
		res = res * 10 + (c - '0');
		c = fgetc(f);
	}
	if (flag == 0)
		return ungetc(c, f), 0;
	if (c != EOF)
		ungetc(c, f);
	int *x = va_arg(ap, int *);
	*x = res * sign;
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
	int c;
	int i = 0;
	int flag = 0;
	char *str = va_arg(ap, char *);
	c = fgetc(f);
	if (c == EOF)
		return -1;
	while (!isspace(c))
	{
		if (c == EOF)
			break;
		str[i] = c;
		flag = 1;
		c = fgetc(f);
		i++;
	}
	str[i] = '\0';
	if (flag == 0)
		return 0;
	if (c != EOF)
		ungetc(c,f);
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

int main()
{
	int		a;
	int		b;
	int		c;
	char	ch;

	// int ret = ft_scanf("%d %d %d", &a, &b, &c);
	// printf("return value ==> %d, a ==> %d, b ==>> %d, c ==>> %d\n", ret, a, b, c);
	int	ret = ft_scanf(" ");
	printf("return value ==> '%d', character ==> '%c'\n", ret, c);
}