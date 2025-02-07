# CFLAGS = -Wall -Wextra -Werror 

NAME = pipex

SRCS = ft_split.c helper.c pipex.c check_path.c initialize_data.c error_message.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	cc $(CFLAGS)  $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all

.SECONDARY: $(OBJS)

