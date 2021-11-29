#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	char *var = "asd";
	printf("0%-8p0\n", *var);
}