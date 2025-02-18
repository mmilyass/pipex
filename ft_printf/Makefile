FLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

SRCS = ft_printf.c ft_putaddress.c ft_putchar.c \
		ft_putnbr_hex_low.c ft_putnbr_hex.c \
		ft_putnbr_unsigned.c ft_putnbr.c \
		ft_putstr_if_null.c for_addresse.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

%.o: %.c
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJS)