/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonio <antonio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:14:57 by antonio           #+#    #+#             */
/*   Updated: 2021/12/03 15:24:06 by antonio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // write
#include <stdarg.h> // for variadic function
#include <stdlib.h> // malloc

size_t	ft_strlen(const char *s)
{
	size_t	i;

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

int	ft_atoi(const char *str)
{
	int	number;
	int	sign;

	sign = 1;
	number = 0;
	while (*str == ' ' || *str == '\f' || *str == '\n' || *str == '\r'
		|| *str == '\t' || *str == '\v')
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

int	number_of_digits(long long nb)
{
	int	i;

	i = 1;
	if (nb < 0)
		nb *= -1;
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

void	pass_int_to_str(long long *nb, char *str, int *i)
{
	while (*nb > 0)
	{
		str[*i] = (*nb % 10) + 48;
		*nb /= 10;
		*i -= 1;
	}
}

char	*ft_itoa(int n)
{
	char		*str;
	long long	nb;
	int			i;

	nb = n;
	i = number_of_digits(nb);
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	str[i--] = 0;
	if (nb < 0)
		nb *= -1;
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	pass_int_to_str(&nb, str, &i);
	return (str);
}

char	*ft_itoa_unsigned_int(unsigned int n)
{
	char		*str;
	long long	nb;
	int			i;

	nb = n;
	i = number_of_digits(nb);
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	str[i--] = 0;
	if (nb < 0)
		nb *= -1;
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	pass_int_to_str(&nb, str, &i);
	return (str);
}

typedef struct t_print_settings
{
	va_list	args;
	int		hash;
	int		zero;
	int		dash;
	int		space;
	int		plus;
	int		width;
	int		precision;
	int		point;
	int		t_length;
}	t_settings;

t_settings	*ft_initialise_tab(t_settings *tab)
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

t_settings	*set_tab(t_settings *tab)
{
	int	i;

	i = tab->t_length;
	ft_initialise_tab(tab);
	tab->t_length = i;
	return (tab);
}

void	ft_print_padding(t_settings *tab, char pad, int times)
{
	int	i;

	i = -1;
	while (++i < times)
		tab->t_length += write(1, &pad, 1);
}

void	ft_print_percent(t_settings *tab, char percent)
{
	tab->t_length += write(1, &percent, 1);
	set_tab(tab);
}

void	ft_print_char(t_settings *tab)
{
	char	a;

	a = va_arg(tab->args, int);
	if (tab->width && !tab->dash)
		ft_print_padding(tab, ' ', (tab->width - 1));
	tab->t_length += write(1, &a, 1);
	if (tab->width && tab->dash)
		ft_print_padding(tab, ' ', (tab->width - 1));
	set_tab(tab);
}

void	ft_print_s_dash(t_settings *tab, const char *str)
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

void	ft_print_s_no_dash(t_settings *tab, const char *str)
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

void	ft_print_string(t_settings *tab)
{
	char	*str;
	int		i;

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

int	ft_count_digits(unsigned long i)
{
	int	x;

	x = 1;
	while (i > 9)
	{
		i = i / 10;
		x++;
	}
	return (x);
}

char	*ft_putnbr_base(char *str, unsigned long nbr, char *base)
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

char	*long_to_string(unsigned long i)
{
	char	*str;
	char	*mem;

	str = malloc(ft_count_digits(i) + 3);
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

void	ft_print_p_zero_pad(t_settings *tab, char *str)
{
	char	*ptr;
	int		i;
	char	*mem;

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
		while (*str)
			*mem++ = *str++;
		*mem = '\0';
		tab->t_length += write(1, ptr, ft_strlen(ptr));
		free(ptr);
	}
}

void	ft_print_void(t_settings *tab)
{
	unsigned long	nbr;
	char			*str;

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

char	*ft_add_char_to_beg_str(char *str, int times, char a)
{
	char	*str_mem;
	char	*ptr;
	char	*mem;

	str_mem = str;
	ptr = malloc(times + ft_strlen(str) + 1);
	if (!ptr)
		return (NULL);
	mem = ptr;
	while (times--)
		*mem++ = a;
	while (*str)
		*mem++ = *str++;
	*mem = '\0';
	free(str_mem);
	return (ptr);
}

char	*ft_add_char_to_end_str(char *str, int times, char a)
{
	char	*str_mem;
	char	*ptr;
	char	*mem;

	str_mem = str;
	ptr = malloc(times + ft_strlen(str) + 1);
	if (!ptr)
		return (NULL);
	mem = ptr;
	while (*str)
		*mem++ = *str++;
	while (times--)
		*mem++ = a;
	*mem = '\0';
	free(str_mem);
	return (ptr);
}

void	ft_print_dec_update_tab(t_settings *tab)
{
	if (tab->plus && tab->space)
		tab->space = 0;
	if (tab->zero && tab->dash)
		tab->zero = 0;
	if (tab->point && tab->zero)
		tab->zero = 0;
}

void	print_dec_num_block(t_settings *tab, char *str)
{
	if (tab->width > ft_strlen(str) && tab->dash)
		str = ft_add_char_to_end_str(str, tab->width - ft_strlen(str), ' ');
	else if (tab->width > ft_strlen(str) && tab->zero)
		str = ft_add_char_to_beg_str(str, tab->width - ft_strlen(str), '0');
	else if (tab->width > ft_strlen(str))
		str = ft_add_char_to_beg_str(str, tab->width - ft_strlen(str), ' ');
	tab->t_length += write(1, str, ft_strlen(str));
	free(str);
	set_tab(tab);
}

void	ft_print_dec_num(t_settings *tab)
{
	int		nbr;
	char	*str;
	char	*ptr;

	nbr = va_arg(tab->args, int);
	if (!nbr && !tab->precision && tab->point)
	{
		str = malloc(1);
		*str = '\0';
	}
	else
		str = ft_itoa(nbr);
	ft_print_dec_update_tab(tab);
	if (tab->precision > ft_strlen(str))
		str = ft_add_char_to_beg_str(str, tab->precision - ft_strlen(str), '0');
	if (nbr < 0)
		str = ft_add_char_to_beg_str(str, 1, '-');
	else if (tab->plus)
		str = ft_add_char_to_beg_str(str, 1, '+');
	else if (tab->space)
		str = ft_add_char_to_beg_str(str, 1, ' ');
	print_dec_num_block(tab, str);
}

void	print_unsigned_dec_block(t_settings *tab, char *str)
{
	tab->t_length += write(1, str, ft_strlen(str));
	free(str);
	set_tab(tab);
}

void	ft_print_unsigned_dec(t_settings *tab)
{
	unsigned int	nbr;
	char			*str;
	char			*ptr;

	nbr = va_arg(tab->args, unsigned int);
	if (!nbr && !tab->precision && tab->point)
	{
		str = malloc(1);
		*str = '\0';
	}
	else
		str = ft_itoa_unsigned_int(nbr);
	ft_print_dec_update_tab(tab);
	if (tab->precision > ft_strlen(str))
		str = ft_add_char_to_beg_str(str, tab->precision - ft_strlen(str), '0');
	if (tab->width > ft_strlen(str) && tab->dash)
		str = ft_add_char_to_end_str(str, tab->width - ft_strlen(str), ' ');
	else if (tab->width > ft_strlen(str) && tab->zero)
		str = ft_add_char_to_beg_str(str, tab->width - ft_strlen(str), '0');
	else if (tab->width > ft_strlen(str))
		str = ft_add_char_to_beg_str(str, tab->width - ft_strlen(str), ' ');
	print_unsigned_dec_block(tab, str);
}

char	*ft_uns_int_dec_to_hex(unsigned int i, char a)
{
	char	*str;
	char	*mem;

	str = malloc(ft_count_digits(i) + 1);
	if (!str)
		return (NULL);
	mem = str;
	if (a == 'x')
		mem = ft_putnbr_base(mem, i, "0123456789abcdef");
	else
		mem = ft_putnbr_base(mem, i, "0123456789ABCDEF");
	*mem = '\0';
	return (str);
}

void	print_num_hex_block(t_settings *tab, char *str, char l)
{
	if (tab->hash && l == 'x')
		str = ft_add_char_to_beg_str(str, 1, 'x');
	else if (tab->hash && l == 'X')
		str = ft_add_char_to_beg_str(str, 1, 'X');
	if (tab->hash)
		str = ft_add_char_to_beg_str(str, 1, '0');
	if (tab->width > ft_strlen(str) && tab->dash)
		str = ft_add_char_to_end_str(str, tab->width - ft_strlen(str), ' ');
	else if (tab->width > ft_strlen(str) && !tab->zero)
		str = ft_add_char_to_beg_str(str, tab->width - ft_strlen(str), ' ');
	tab->t_length += write(1, str, ft_strlen(str));
	free(str);
	set_tab(tab);
}

void	ft_print_num_hex(t_settings *tab, char l)
{
	unsigned int	nbr;
	char			*str;
	char			*ptr;

	nbr = va_arg(tab->args, unsigned int);
	if (!nbr && !tab->precision && tab->point)
	{
		str = malloc(1);
		*str = '\0';
	}
	else
		str = ft_uns_int_dec_to_hex(nbr, l);
	ft_print_dec_update_tab(tab);
	if (tab->precision > ft_strlen(str))
		str = ft_add_char_to_beg_str(str, tab->precision - ft_strlen(str), '0');
	if (tab->width > ft_strlen(str) && tab->zero && !tab->hash)
		str = ft_add_char_to_beg_str(str, tab->width - ft_strlen(str), '0');
	else if (tab->width > (ft_strlen(str) + 2) && tab->zero && tab->hash)
		str = ft_add_char_to_beg_str(str, tab->width - ft_strlen(str) - 2, '0');
	print_num_hex_block(tab, str, l);
}

int	ft_is_format(char letter, char *conversions)
{
	int	i;

	i = -1;
	while (conversions[++i])
		if (letter == conversions[i])
			return (1);
	return (0);
}

int	ft_convert(t_settings *tab, const char *format, int i)
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
	else if (format[i] == 'd' || format[i] == 'i')
		ft_print_dec_num(tab);
	else if (format[i] == 'u')
		ft_print_unsigned_dec(tab);
	else if (format[i] == 'x')
		ft_print_num_hex(tab, 'x');
	else if (format[i] == 'X')
		ft_print_num_hex(tab, 'X');
	return (i);
}

int	ft_analise_precision(t_settings *tab, const char *format, int i)
{
	int		j;
	char	*precision;

	tab->point = 1;
	j = i;
	if (format[i] > 48 && format[i] < 58)
		while (format[i] > 47 && format[i] < 58)
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

int	ft_analise_width(t_settings *tab, const char *format, int i)
{
	int		j;
	char	*width;

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

int	is_flag(char letter, char *flags)
{
	int	i;

	i = -1;
	while (flags[++i])
		if (flags[i] == letter)
			return (1);
	return (0);
}

int	ft_analise_flags(t_settings *tab, const char *format, int i)
{
	while (is_flag(format[i], "-0# +"))
	{
		if (format[i] == '-')
			tab->dash = 1;
		else if (format[i] == '0')
			tab->zero = 1;
		else if (format[i] == '#')
			tab->hash = 1;
		else if (format[i] == ' ')
			tab->space = 1;
		else if (format[i] == '+')
			tab->plus = 1;
		i++;
	}
	i = ft_analise_width(tab, format, i);
	return (i);
}

int	ft_printf(const char *format, ...)
{
	t_settings	*tab;
	int			i;
	int			t_printed;

	tab = malloc(sizeof(t_settings));
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
