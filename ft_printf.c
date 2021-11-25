#include <unistd.h>
#include <stdio.h> // official printf
#include <stdarg.h>

typedef struct print_settings
{
	va_list args;
	int width;
	int precision;
	int zero;
	int point;
	int dash;
	int t_length;
	int sign;
	int is_zero;
	int percentage;
	int space_f;
} str_settings;

str_settings *ft_initialise_tab(str_settings *tab)
{
	tab->width = 0;
	tab->precision = 0;
	tab->zero = 0;
	tab->point = 0;
	tab->sign = 0;
	tab->t_length = 0;
	tab->is_zero = 0;
	tab->dash = 0;
	tab->percentage = 0;
	tab->space_f = 0;
	return (tab);
}

int ft_printf(const char *format, ...)
{
	str_settings *tab;

	tab = (str_settings *)malloc(sizeof(tab));
	if (!tab)
		return (-1);
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