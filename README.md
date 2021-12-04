42_Project


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
  
- p conversions ----  
cares for:  
-width  
-dash  
-zero (but it gives warning: undefined behaviour) (ex: (%p - 0x61) (%08p - 0x000061))  
  
- d conversions ----  
('+' and ' ') -- ignore ' '  
(0 and -) -- ignore 0  
(. and 0) -- ignore 0  
'.' - gives the minimum number of digits to appear (puts zeros at the left)  
1 - convert number to string without sign  
2 - if precision > strlen(str) : add zeros to beguining of str  
3 - if ((nbr < 0) || (nbr > 0 && (space || plus))) : add sign/space to beguining of str  
4 - if width > ft_strlen:  
		if (dash) : add spaces to end of str  
		else if (zero) : add zeros to beguining of str   
		else : add spaces to beguining of str  
  
- i conversions ----  
- same as d conversion  
   
- u conversions ----  
- same as d conversion a side from:  
	- va_arg receives an unsigned int (instead of a int)  
	- itoa has to receive an unsigned int (instead of a int)  
	- '+' and ' ' flags are ignored  
	- and obviously no need to verify if nbr < 0   
  
- x and X conversions ----  
if '#' add '0x' to beguining of number  
ignore (' ' and '+')  
flags to care for: '-' , '0' and '#'  
precision min size doesn't include '0x'  
width min size does include '0x'  
