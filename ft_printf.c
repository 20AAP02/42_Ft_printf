#include <unistd.h>
#include <stdio.h> // official printf
#include <stdarg.h>


/* NOTAS

order:
1 - %
2 - zero or more flags
3 - optional minimum field width
4 - optional precision
5 - optional length modifier 

*/

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
	int star;
	int t_length;
} str_settings;


int	ft_isalpha(int c)
{
	if (c > 64 && c < 91)
		return (1);
	else if (c > 96 && c < 123)
		return (1);
	else
		return (0);
}

str_settings *ft_initialise_tab(str_settings *tab)
{
	tab->width = 0;
	tab->precision = 0;
	tab->zero = 0;
	tab->point = 0;
	tab->sign = 0;
	tab->t_length = 0;
	tab->dash = 0;
	tab->space = 0;
	return (tab);
}

int ft_analise_format(str_settings *tab, const char *format, int i)
{
	if (format[i] == '%')
	{
		write(1, &format[i], 1);
		tab->t_length += 1;
		return (i);
	}
	return (i);
}

int ft_printf(const char *format, ...)
{
	str_settings *tab;
	int	i;
	int	t_printed;

	tab = (str_settings *)malloc(sizeof(tab));
	if (!tab)
		return (-1);
	ft_initialise_tab(tab);
	va_start(tab->args, format);
	i = -1;
	t_printed = 0;
	while (format[++i])
	{
		if (format[i] == '%')
			i = ft_analise_format(tab, format, i + 1);
		else
			t_printed += write(1, &format[i], 1);
	}
	va_end(tab->args);
	t_printed += tab->t_length;
	free(tab);
	return(t_printed);
}

int main()
{
	int a, b, c;
	char s[] = "este ano";
	a = 24;
	b = 11;
	c = 2021;
	printf("(Dia: %.i) (Mes: %02i) (Ano: %04i) (Descricao: %s)\n", a, b, c, s);
	printf(s);
	return (0);
}