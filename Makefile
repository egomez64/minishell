NAME = minishell

LIBFT = libft/libft.a

CC = cc

SRCS = src/parsing/lexing.c src/parsing/token_list.c

HEADERS = minishell.h

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft

ifdef DEBUG
CFLAGS = -Wall -Wextra -Iincludes -Ilibft -g
endif

ifdef CHECK
CFLAGS += -fsanitize=address
endif

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@

$(LIBFT):
	@make -j8 -C libft/ all

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -f $(OBJS)
	@make -C libft/ clean
	
fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all fclean clean re