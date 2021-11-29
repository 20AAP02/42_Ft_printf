#include <stdio.h>

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

int main()
{
	char a = 'c';
	printf("0%-2.0c0\n", a);
}