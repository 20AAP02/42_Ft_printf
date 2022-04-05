<h1 align="center"> Ft_printf | 42 School Project </h1>
<h4>Because putnbr() and putstr() aren’t enough</h4>
<p>This project was pretty straightforward, I had to recode printf.</p>
<p>The mandatory part of this project didn't include printf's flags, but since I also did the bonus, this implementation of printf includes almost all printf flags, plus precision and width.</p> 

-----

<h4>What I learned with this project?</h4>
<p>- I learned about variadic functions and how to implement those</p>
<p>- I learned more about printf options 😏</p>

-----

<h4>Subject</h4>
https://github.com/20AAP02/ft_printf/blob/master/en.subject.pdf

-----

<h4>Grade : 125%</h4>
<h6>Mandatory : 100/100</h6>
<h6>Bonus : 25/25</h6>

-----

<h4>Create library that contains ft_printf</h4>

```
git clone https://github.com/20AAP02/42_Ft_printf.git ft_printf
cd ft_printf
make
```

-----

<h3>My Aproach</h3>
<p>
Ft_printf is a project that mimics the real printf function.
Although wide in scope, it’s not a difficult project (aside from having to discover all the possible combination of flags through testing).
</p>
<p>If you are interest to build your own implementation of printf, there are already some articles out there. If you find yourself stuck, without kwnowing where to start I would recommend you to read this one: https://csnotes.medium.com/ft-printf-tutorial-42project-f09b6dc1cd0e </p>

<p>Has I have said, the hardest part, is to mimic all the possible combinations of flags that printf has. So I tried to keep some notes of this combinations while I discovered them throught some testing. Here they are. It might be a bit desorganized, but I hope it helps...</p>

<h4>- The order you must read the flags</h4> 
<p>1st - %</p>
<p>2sd - zero or more flags</p>
<p>3th - optional minimum field width</p>
<p>4th - optional precision</p>
<p>5th - the conversion letter/sign (csdiupxX%)</p>

<h4>- The Flags (#0-+ and ' ')</h4>   
  
(# with x/X) -- add 0x/X to the beguining of the number  
0 -- the value should be zero padded  
(0 and -) -- ignore 0  
(diuxX with . and 0) -- ignore 0 (other conversions the behavior is undefined)  
('-') -- the value is to be left adjusted (padded with blanks in the right)  
(' ') -- a blank before positive number  
('+') -- put sign before number  
('+' and ' ') -- ignore ' '  

<h4>- Minimum field width</h4>  
  
if converted value has fewer characters than the field width, pad with spaces   
  
<h4>Precision (.)</h4> 
  
(if only '.') -- precision is zero  
(with diuxX) -- gives the minimum number of digits to appear  
(with s) -- gives the maximum number of characters to be printed  
  
- c conversions ----  
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
same as d conversion  
   
- u conversions ----  
same as d conversion a side from:  
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
