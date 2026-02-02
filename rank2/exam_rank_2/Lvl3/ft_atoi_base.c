/* Assignment name  : ft_atoi_base
Expected files   : ft_atoi_base.c
Allowed functions: None
--------------------------------------------------------------------------------

Write a function that converts the string argument str (base N <= 16)
to an integer (base 10) and returns it.

The characters recognized in the input are: 0123456789abcdef
Those are, of course, to be trimmed according to the requested base. For
example, base 4 recognizes "0123" and base 16 recognizes "0123456789abcdef".

Uppercase letters must also be recognized: "12fdb3" is the same as "12FDB3".

Minus signs ('-') are interpreted only if they are the first character of the
string.

Your function must be declared as follows:

int	ft_atoi_base(const char *str, int str_base); */

#include <unistd.h>

char to_lower (char c)
{
	if (c>= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int get_digit(char c, int digits_in_base)
{
	int max_digit;

	if(digits_in_base <= 10)
		max_digit = digits_in_base - 1 + '0';
}

int ft_atoi_base(const char *str, int str_base)
{
	int result = 0;
	int sign = 1;
	int digit;

	if (str == NULL || str_base < 2 || str_base > 16)
		return 0;
	if (*str == '-')
	{
		sign = -1;
		++str;
	}

	while (*str)
	{
		digit = get_digit(to_lower(*str), str_base);
		if (digit == -1)
			break;
		result = result * str_base + digit;
		++str;
	}
	return (result * sign);
}