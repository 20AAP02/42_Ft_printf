CC 				= gcc
CFLAGS	= -Wall -Wextra -Werror
LIB1	= ar -rcs
LIB2	= ranlib
RM				= /bin/rm -f

NAME	= libftprintf.a

INCLUDE = .
SRCS	= ft_printf_functions0.c ft_printf_functions1.c \
					ft_printf_functions2.c ft_printf_functions3.c \
					ft_printf_functions4.c ft_printf_functions5.c \
					ft_printf_functions6.c  ft_printf.c
OBJS	= $(SRCS:.c=.o)

all: 		$(NAME) clean

$(NAME): 	$(OBJS) $(INCLUDE)
					$(LIB1) $(NAME) $(OBJS)
					$(LIB2) $(NAME)

.c.o:
					$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $(<:.c=.o)
clean:
					$(RM) $(OBJS)
fclean: 	clean
					$(RM) $(NAME)

re: 				fclean all

.PHONY:		all clean fclean re