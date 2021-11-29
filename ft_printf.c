#include <unistd.h>
#include <stdio.h> // official printf
#include <stdarg.h>
#include <stdlib.h>

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

int ft_count_digits(unsigned long i)
{
	int x;

	x = 1;
	while (i > 9)
	{
		i = i / 10;
		x++;
	}
	return (x);
}

char *ft_putnbr_base(char *str, unsigned long nbr, char *base)
{
	unsigned long	base_size;
	unsigned long	x;

	base_size = ft_strlen(base);
	if (nbr < base_size)
	{
		*str = base[nbr];
		str++;
	}
	else
	{
		x = nbr / base_size;
		str = ft_putnbr_base(str, x, base);
		x = nbr % base_size;
		*str = base[x];
		str++;
	}
	return (str);
}

char *long_to_string(unsigned long i)
{
	char *str;
	char *mem;

	str = malloc(sizeof(ft_count_digits(i) + 3));
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = 'x';
	mem = str;
	mem += 2;
    mem = ft_putnbr_base(mem, i, "0123456789abcdef");
	*mem = '\0';
	return (str);
}

void ft_print_p_zero_pad(frt_settings *tab, char *str)
{
	char *ptr;
	int i;
	char *mem;

	if (tab->width <= ft_strlen(str))
		tab->t_length += write(1, str, ft_strlen(str));
	else
	{
		i = 0;
		ptr = malloc(tab->width + 1);
		if (!ptr)
			return ;
		mem = ptr;
		*mem++ = '0';
		*mem++ = 'x';
		while (i++ < (tab->width - ft_strlen(str)))
			*mem++ = '0';
		str += 2;
		while(*str)
			*mem++ = *str++;
		*mem = '\0';
		tab->t_length += write(1, ptr, ft_strlen(ptr));
		free(ptr);
	}
}

void ft_print_void(frt_settings *tab)
{
	unsigned long nbr;
	char *str;

	nbr = (unsigned long)va_arg(tab->args, void *);
	str = long_to_string(nbr);
	if (tab->width && tab->dash)
	{
		tab->t_length += write(1, str, ft_strlen(str));
		ft_print_padding(tab, ' ', (tab->width - ft_strlen(str)));
	}
	else if (tab->width && tab->zero)
		ft_print_p_zero_pad(tab, str);
	else if (tab->width > ft_strlen(str))
	{
		tab->t_length += write(1, " ", (tab->width - ft_strlen(str)));
		tab->t_length += write(1, str, ft_strlen(str));
	}
	else
		tab->t_length += write(1, str, ft_strlen(str));
	free(str);
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
	else if (format[i] == 'p')
		ft_print_void(tab);
	/*else if (format[i] == 'd')
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
	ft_printf("0%-05.0p0\n", a);
}