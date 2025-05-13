#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
        // Some code here
	int	ch = fgetc(f);
	while (ch != EOF && isspace(ch))
		ch = fgetc(f);
	if (ch == EOF)
		return (-1);
	ungetc(ch, f);
	return 1;
}
// 	return 1;

int match_char(FILE *f, char c)
{
        // Some code here
	int	ch = fgetc(f);
	if (ch == EOF || ch != c)
		return (-1);
	ungetc(ch, f);
	return 1;
}

int scan_char(FILE *f, va_list ap)
{
        // Some code here
	char*	ch;
	int		c;

	ch = va_arg(ap, char *);
	c = fgetc(f);
	if (c == EOF)
		return (-1);
	*ch = c;
	return 1;
}

int scan_int(FILE *f, va_list ap)
{
        // Some code here

	return 1;
}

int scan_string(FILE *f, va_list ap)
{
    // Some code here
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

int	main(void)
{
	int c;
	// ft_scanf("%c", &c);
	// printf("%c\n", c);
	ft_scanf(" ");
}
