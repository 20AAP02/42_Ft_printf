#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
- x and X conversions ----
if '#' add '0x' to beguining of number
ignore (' ' and '+')
flags to care for: '-' , '0' and '#'
precision min size doesn't include '0x'
width min size does include '0x'
*/

int	main(void)
{
	unsigned int i = 5;
	printf("0%#8x0\n", i);
}