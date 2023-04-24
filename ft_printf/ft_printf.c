#include <unistd.h>
#include <stdarg.h>

void	put_string(char *string, int *len)
{
	if (!string)
		string = "(null)";
	while (*string)
		*len += write(1, string++, 1);
}

void	put_digit(long long int number, int base, int *len)
{
	char	*hexadecimal = "0123456789abcdef";

	if (number < 0)
	{
		number *= -1;
		*len += write(1, "-", 1);
	}
	if (number >= base)
		put_digit((number / base), base, len);
	*len += write(1, &hexadecimal[number % base], 1);
}

int	ft_printf(const char *av, ...)
{
	int len = 0;

	va_list	pt;
	va_start(pt, av);

	while (*av)
	{
		if ((*av == '%') && ((*(av + 1) == 's') || (*(av + 1) == 'd') || (*(av + 1) == 'x')))
		{
			av++;
			if (*av == 's')
				put_string(va_arg(pt, char *), &len);
			else if (*av == 'd')
				put_digit((long long int)va_arg(pt, int), 10, &len);
			else if (*av == 'x')
				put_digit((long long int)va_arg(pt, unsigned int), 16, &len);
		}
		else
			len += write(1, av, 1);
		av++;
	}
	return (va_end(pt), len);
}
