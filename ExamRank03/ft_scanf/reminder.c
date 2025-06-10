#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c;
    while ((c = fgetc(f)) != EOF && isspace(c))
        ;
    if (c == EOF)
        return -1;
    ungetc(c, f);
    return 1;
}

int match_char(FILE *f, char c)
{
    int input = fgetc(f);
    if (input == EOF)
        return -1;
    if (input == c)
        return 1;
    ungetc(input, f);
    return -1;
}

int scan_char(FILE *f, va_list ap)
{
    char *ptr = va_arg(ap, char *);
    int c = fgetc(f);
    if (c == EOF)
        return -1;
    *ptr = (char)c;
    return 1;
}

int scan_int(FILE *f, va_list ap)
{
    int sign = 1;
    int value = 0;
    int c = fgetc(f);
    
    if (c == '-') {
        sign = -1;
        c = fgetc(f);
    } else if (c == '+') {
        c = fgetc(f);
    }
    
    if (!isdigit(c)) {
        if (c != EOF)
            ungetc(c, f);
        return -1;
    }
    
    while (isdigit(c)) {
        value = value * 10 + (c - '0');
        c = fgetc(f);
    }
    
    if (c != EOF)
        ungetc(c, f);
    
    *va_arg(ap, int *) = value * sign;
    return 1;
}

int scan_string(FILE *f, va_list ap)
{
    char *str = va_arg(ap, char *);
    int c;
    int count = 0;
    
    while ((c = fgetc(f)) != EOF && !isspace(c)) {
        str[count++] = c;
    }
    
    if (c != EOF)
        ungetc(c, f);
    
    if (count == 0)
        return -1;
    
    str[count] = '\0';
    return 1;
}

int	main(void)
{
	int r = scanf(" ");
	printf("%d\n", r);
}