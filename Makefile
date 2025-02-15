CFLAGS = -Wall -Wextra -Werror

NAME = pipex

LIBFT_DIR = libft

LIBFT = libft.a

SRCS = pipex.c check_path.c initialize_data.c error_message.c put_rest.c ft_split.c \
		get_next_line/get_next_line.c my_touch.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME) 


$(NAME) :$(LIBFT) $(OBJS)
	cc $(CFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFT) -o $(NAME)

bonus: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f libft.a
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: clean fclean re all bonus

.SECONDARY: $(OBJS) $(LIBFT)


