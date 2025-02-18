CFLAGS = -Wall -Wextra -Werror

NAME = pipex

LIBFT_DIR = libft

LIBFT = libft.a

FT_PRINTF = libftprintf.a

SRCS = pipex.c check_path.c initialize_data.c error_message.c put_rest.c get_next_line/ft_split.c \
		get_next_line/get_next_line.c my_touch.c handle_files_open_close.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(FT_PRINTF) $(NAME) 


$(NAME) :$(LIBFT) $(FT_PRINTF) $(OBJS) 
	cc $(CFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFT) ft_printf/$(FT_PRINTF) -o $(NAME)

bonus: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(FT_PRINTF):
	@make -C ft_printf

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C ft_printf clean

fclean: clean
	rm -f $(NAME)
	rm -f libft.a
	make -C $(LIBFT_DIR) fclean
	make -C ft_printf fclean

re: fclean all

.PHONY: clean fclean re all bonus

.SECONDARY: $(OBJS) $(LIBFT) $(FT_PRINTF)


