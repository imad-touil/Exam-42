#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c;
    
    while ((c = fgetc(f)) != EOF && isspace(c))
        ;
        
    if (c == EOF) {
        if (ferror(f))
            return -1;
        if (feof(f))
            return -1;
    }
    ungetc(c, f);
    return 1;
}

int match_char(FILE *f, char expected)
{
    int c = fgetc(f);
    
    if (c == EOF)
        return -1;
        
    if (c != expected) {
        ungetc(c, f);
        return 0;
    }
    return 1;
}

int scan_char(FILE *f, va_list ap)
{
    int c = fgetc(f);
    
    if (c == EOF)
        return -1;
        
    *va_arg(ap, char *) = (char)c;
    return 1;
}

int scan_int(FILE *f, va_list ap)
{
    int c;
    int sign = 1;
    int value = 0;
    int digits = 0;
    int *ptr = va_arg(ap, int *);
    

    c = fgetc(f);
    if (c == EOF)
        return -1;
    ungetc(c, f);
    
    c = fgetc(f);
    if (c == '-') {
        sign = -1;
    } else if (c == '+') {
        sign = 1;
    } else {
        ungetc(c, f);
    }
    
    while ((c = fgetc(f)) != EOF && isdigit(c)) {
        value = value * 10 + (c - '0');
        digits++;
    }
    if (c != EOF)
        ungetc(c, f);
    if (digits == 0)
        return 0;
    *ptr = value * sign;
    return 1;
}

int scan_string(FILE *f, va_list ap)
{
    int c;
    char *str = va_arg(ap, char *);
    int chars_read = 0;
    c = fgetc(f);
    if (c == EOF)
        return -1;
    ungetc(c, f);
    while ((c = fgetc(f)) != EOF && !isspace(c)) {
        str[chars_read++] = c;
    }
    if (c != EOF)
        ungetc(c, f);
    if (chars_read == 0)
        return 0;
    str[chars_read] = '\0';
    return 1;
}

int match_conv(FILE *f, const char **format, va_list ap)
{
    int result;

    int c = fgetc(f);
    if (c == EOF)
        return -1;
    ungetc(c, f);
    
    switch (**format)
    {
        case 'c':
            result = scan_char(f, ap);
            break;
        case 'd':
            match_space(f);
            result = scan_int(f, ap);
            break;
        case 's':
            match_space(f);
            result = scan_string(f, ap);
            break;
        case EOF:
            return -1;
        default:
            return -1;
    }
    if (feof(f) && result <= 0)
        return -1;
        
    return result;
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
    int nconv = 0;
    int result;

    int c = fgetc(f);
    if (c == EOF)
        return EOF;
    ungetc(c, f);

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            result = match_conv(f, &format, ap);
            if (result == 1)
                nconv++;
            else if (result == -1 || feof(f))
                return nconv == 0 ? EOF : nconv; 
        }
        else if (isspace(*format))
        {
            if (match_space(f) == -1 || feof(f)) 
                return nconv == 0 ? EOF : nconv;
        }
        else if (match_char(f, *format) != 1)
            break;
        format++;
    }
    
    if (ferror(f) || (feof(f) && nconv == 0))
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
// int	main(void)
// {
// 	char	str1[100];
// 	char	str2[100];
// 	int		num1;
// 	int		num2;
// 	int	b1 = ft_scanf("%s %s", str1, str2);
// 	printf("|   %s  %s  |\n", str1, str2);
// 	printf("return value from ft_scanf ==> %d\n", b1);
// }

int	main(void)
{
	int	ret;
	int d;

	ret = ft_scanf("%d", &d);
	printf("this is the character %d, && this is the return value %d\n", d, ret);
}
