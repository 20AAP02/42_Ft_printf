#include <unistd.h>
#include <stdio.h> // official printf
#include <stdarg.h>
#include <stdlib.h>

/* NOTAS

order:
1 - %
2 - zero or more flags
3 - optional minimum field width
4 - optional precision

conversions: (csdiupxX% with #0-+ and ' ') ----

(# with x/X) -- add 0x/X to the beguining of the number
0 -- the value should be zero padded
(0 and -) -- ignore 0
(diuxX with . and 0) -- ignore 0 (other conversions the behavior is undefined)
('-') -- the value is to be left adjusted (padded with blanks in the right)
(' ') -- a blank before positive number
('+') -- put sign before number
('+' and ' ') -- ignore ' '

minimum field width: -----

if converted value has fewer characters than the field width, pad with spaces 

precision:'.' ----

(if only '.') -- precision is zero
(with diuxX) -- gives the minimum number of digits to appear
(with s) -- gives the maximum number of characters to be printed


- c conversion ----
care for:
-width
-dash
if '-' with width: left align (number of padding = width - 1)

- s conversions ----
care for:
-width
-dash
-precision
-if '-' with width: left align (number of padding = width - len(s))
-precision gives the maximum number of characters to be written 
(deleting letters from the end)

- d conversions ----
('+' and ' ') -- ignore ' '
(0 and -) -- ignore 0
(. and 0) -- ignore 0
'.' - gives the minimum number of digits to appear (puts zeros at the left)
1 - convert number to string
2 - if  (!('.' || '-') && (width)): add (width - len(string)) zeros to beguining of str
3 - if + and number is positive add + to the first char of string unless that is != 0 (in that case add to before the first char)

*/

size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	index;

	if (!s)
		return (NULL);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	index = 0;
	while (index < len && s[start + index])
	{
		ptr[index] = s[start + index];
		index++;
	}
	ptr[index] = '\0';
	return (ptr);
}

int ft_atoi(const char *str)
{
	int number;
	int sign;

	sign = 1;
	number = 0;
	while (*str == ' ' || *str == '\f' || *str == '\n' || *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str > 47 && *str < 58)
	{
		number = (number * 10) + (*str - 48);
		str++;
	}
	return (number * sign);
}

typedef struct print_settings
{
	va_list args;
	int hash;
	int zero;
	int dash;
	int space;
	int plus;
	int width;
	int precision;
	int point;
	int t_length;
} frt_settings;

frt_settings *ft_initialise_tab(frt_settings *tab)
{
	tab->hash = 0;
	tab->zero = 0;
	tab->dash = 0;
	tab->space = 0;
	tab->plus = 0;
	tab->width = 0;
	tab->precision = 0;
	tab->point = 0;
	tab->t_length = 0;
	return (tab);
}

frt_settings *set_tab(frt_settings *tab)
{
	int i;

	i = tab->t_length;
	ft_initialise_tab(tab);
	tab->t_length = i;
	return (tab);
}

void ft_print_padding(frt_settings *tab, char pad, int times)
{
	int i;

	i = -1;
	while (++i < times)
		tab->t_length += write(1, &pad, 1);
}

void ft_print_percent(frt_settings *tab, char percent)
{
	char a = percent;
	tab->t_length += write(1, &a, 1);
	set_tab(tab);
}

void ft_print_char(frt_settings *tab)
{
	char a;

	a = va_arg(tab->args, int);
	if (tab->width && !tab->dash)
		ft_print_padding(tab, ' ', (tab->width - 1));
	tab->t_length += write(1, &a, 1);
	if (tab->width && tab->dash)
		ft_print_padding(tab, ' ', (tab->width - 1));
	set_tab(tab);
}

void ft_print_s_dash(frt_settings *tab, const char *str)
{
	if (tab->point && tab->precision <= ft_strlen(str))
	{
		tab->t_length += write(1, str, tab->precision);
		ft_print_padding(tab, ' ', (tab->width - tab->precision));
	}
	else
	{
		tab->t_length += write(1, str, ft_strlen(str));
		ft_print_padding(tab, ' ', (tab->width - ft_strlen(str)));
	}
}

void ft_print_s_no_dash(frt_settings *tab, const char *str)
{
	if (tab->point && tab->precision <= ft_strlen(str))
	{
		ft_print_padding(tab, ' ', (tab->width - tab->precision));
		tab->t_length += write(1, str, tab->precision);
	}
	else
	{
		ft_print_padding(tab, ' ', (tab->width - ft_strlen(str)));
		tab->t_length += write(1, str, ft_strlen(str));
	}
}

void ft_print_string(frt_settings *tab)
{
	char *str;
	int i;

	i = -1;
	str = va_arg(tab->args, char *);

	if (tab->width)
	{
		if (tab->dash)
			ft_print_s_dash(tab, str);
		else
			ft_print_s_no_dash(tab, str);
	}
	else
	{
		if (tab->point && tab->precision <= ft_strlen(str))
			tab->t_length += write(1, str, tab->precision);
		else
			tab->t_length += write(1, str, ft_strlen(str));
	}
	set_tab(tab);
}

int ft_is_format(char letter, char *conversions)
{
	int i;

	i = -1;
	while (conversions[++i])
		if (letter == conversions[i])
			return (1);
	return (0);
}

int ft_convert(frt_settings *tab, const char *format, int i)
{
	while (format[i] && !ft_is_format(format[i], "%cspdiuxX"))
		i++;
	if (format[i] == '%')
		ft_print_percent(tab, format[i]);
	else if (format[i] == 'c')
		ft_print_char(tab);
	else if (format[i] == 's')
		ft_print_string(tab);
	/*else if (format[i] == 'p')
		ft_print_void(tab);
	else if (format[i] == 'd')
		ft_print_dec_num(tab);
	else if (format[i] == 'i')
		ft_print_int(tab);
	else if (format[i] == 'u')
		ft_print_unsigned_dec(tab);
	else if (format[i] == 'x')
		ft_print_num_hex_lower(tab);
	else if (format[i] == 'X')
		ft_print_num_hex_upper(tab);*/
	return (i);
}

int ft_analise_precision(frt_settings *tab, const char *format, int i)
{
	int j;
	char *precision;

	tab->point = 1;
	j = i;
	while (format[i] > 48 && format[i] < 58)
		i++;
	if (j != i)
	{
		precision = ft_substr(format, j, i - j);
		tab->precision = ft_atoi(precision);
		free(precision);
	}
	i = ft_convert(tab, format, i);
	return (i);
}

int ft_analise_width(frt_settings *tab, const char *format, int i)
{
	int j;
	char *width;

	j = i;
	if (format[i] > 48 && format[i] < 58)
		while (format[i] > 47 && format[i] < 58)
			i++;
	if (j != i)
	{
		width = ft_substr(format, j, i - j);
		tab->width = ft_atoi(width);
		free(width);
	}
	if (format[i] == '.')
		i = ft_analise_precision(tab, format, i + 1);
	else
		i = ft_convert(tab, format, i);
	return (i);
}

int is_flag(char letter, char *flags)
{
	int i;

	i = -1;
	while (flags[++i])
		if (flags[i] == letter)
			return (1);
	return (0);
}

int ft_analise_flags(frt_settings *tab, const char *format, int i)
{
	while (is_flag(format[i], "-0# +"))
	{
		if (format[i] == '-')
			tab->dash = 1;
		if (format[i] == '0')
			tab->zero = 1;
		if (format[i] == '#')
			tab->hash = 1;
		if (format[i] == ' ')
			tab->space = 1;
		if (format[i] == '+')
			tab->plus = 1;
		i++;
	}
	i = ft_analise_width(tab, format, i);
	return (i);
}

int ft_printf(const char *format, ...)
{
	frt_settings *tab;
	int i;
	int t_printed;

	tab = malloc(sizeof(frt_settings));
	if (!tab)
		return (-1);
	ft_initialise_tab(tab);
	va_start(tab->args, format);
	i = -1;
	t_printed = 0;
	while (format[++i])
	{
		if (format[i] == '%')
			i = ft_analise_flags(tab, format, i + 1);
		else
			t_printed += write(1, &format[i], 1);
	}
	va_end(tab->args);
	t_printed += tab->t_length;
	free(tab);
	return (t_printed);
}

int main()
{
	char a = 'c';
	ft_printf("0%-2.0c0\n", a);
}