#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
        // You may insert code here
    int c;

    c = fgetc(f);
    if (c == EOF)
        return (-1);
    if (!isspace(c))
        return (ungetc(c, f), 1);
    while ((c = fgetc(f)), c != EOF && isspace(c))
        ;
    if (c != EOF)
        ungetc(c, f);
    return (1);
}

int match_char(FILE *f, char c)
{
        // You may insert code here
    int ch;

    ch = fgetc(f);
    if (ch == c)
        return (1);
    if (ch == EOF)
        return (-1);
    if (ch != c)
        return (ungetc(ch, f), -1);
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
        // You may insert code here
    int c;

    c = fgetc(f);
    if (c == EOF)
        return (-1);
    char *res = va_arg(ap, char *);
    *res = c;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
        // You may insert code here
    int key;
    int num;
    int sign;
    int c;

    key = 0;
    num = 0;
    sign = 1;
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
        key++;
        c = fgetc(f);
    }
    if (c == EOF)
        return (ungetc(c, f));
    if (!key)
        return (ungetc(c, f), 0);
    int *res = va_arg(ap, int *);
    *res = num * sign;
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
        // You may insert code here
    int c;
    int i;
    int key;
    char *res = va_arg(ap, char *);

    c = fgetc(f);
    if (c == EOF)
        return (-1);
    key = 0;
    i = 0;
    while (!isspace(c) && c != EOF)
    {
        res[i] = c;
        c = fgetc(f);
        key++;
        i++;
    }
    res[i] = '\0';
    if (!key)
        return (0);
    // if (c == EOF)
    //     return (-1);
    return (1);
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

// int main()
// {
//     // char c;
//     int a;
//     int b;
//     int c;
//     int ret = ft_scanf("%d %d %d", &a, &b, &c);
//     printf("return ==>> '%d' a ==> '%d', b ==> '%d', c ==> '%d',\n", ret, a, b, c);

//     // char s1[100];
//     // char s2[100];
//     // char s3[100];

//     // int ret = ft_scanf("%s %s %s", s1, s2, s3);
//     // printf("return ==>> '%d' a ==> '%s', b ==> '%s', c ==> '%s',\n", ret, s1, s2, s3);
// }