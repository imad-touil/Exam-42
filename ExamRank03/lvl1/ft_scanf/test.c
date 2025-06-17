#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	int	c;

	c = fgetc(f);
	if (c == EOF)
		return (-1);
	if (!isspace(c))
		return (ungetc(c, f), 1);
	while ((c = fgetc(f)) != EOF && isspace(c))
		;
	if (c != EOF)
		ungetc(c, f);
	return (1);
}

int match_char(FILE *f, char c)
{
        // Some code here
	int	ch;

	ch = fgetc(f);
	if (ch == c)
		return (1);
	if (ch == EOF)
		return (-1);
	if (ch != c)
		return (ungetc(c, f), -1);
	return (0);
}

int scan_char(FILE *f, va_list ap)
{
	int	c;

	c = fgetc(f);
	if (c == EOF)
		return (-1);
	char *res = va_arg(ap, char *);
	*res = c;
	return (1);
}

int scan_int(FILE *f, va_list ap)
{
	int	c;
	int	num;
	int	sign;
	int	key;

	num = 0;
	sign = 1;
	key = 0;
	c = fgetc(f);
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
		c = fgetc(f);
		key++;
	}
	if (c != EOF)
		ungetc(c, f);
	if (!key)
		return (ungetc(c, f), 0);
	int	*res = va_arg(ap, int *);
	*res = num * sign;
	return (1);
}

int scan_string(FILE *f, va_list ap)
{
    int c;
    int key;
    int i;
    char    *str = va_arg(ap, char *);

    i = 0;
    key = 0;
    c = fgetc(f);
    if (c == EOF)
        return (-1);
    while (!isspace(c) && c != EOF)
    {
        str[i] = c;
        c = fgetc(f);
        key++;
        i++;
    }
    str[i] = '\0';
    if (c != EOF)
        ungetc(c, f);
    if (!key)
        return (0);
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
	char	str1[100];
	char	str2[100];
	char	str3[100];

	// int ret = ft_scanf("%d %d %d", &a, &b, &c);
	// printf("return value ==> %d, a ==> %d, b ==>> %d, c ==>> %d\n", ret, a, b, c);
	// int	ret = ft_scanf(" ");
	// printf("return value ==> '%d', character ==> '%c'\n", ret, c);

	int	ret = ft_scanf("%s %s %s", str1, str2, str3);
	printf("return val ==> %d, str1 ==> %s, str2 ==> %s, str3 ==> %s\n", ret, str1, str2, str3);
}
