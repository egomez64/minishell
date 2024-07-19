NAME = minishell
CC = clang
CFLAGS = -Wall -Wextra -Werror  -g -Iincludes -Ilibft
LDFLAGS = -lreadline

ifdef DEBUG
CFLAGS = -Wall -Wextra -Iincludes -Ilibft -g
endif

ifdef CHECK
CFLAGS += -fsanitize=address
endif

LIBFT = libft/libft.a
HEADERS = minishell.h

SRC_DIR	= src
OBJ_DIR	= obj
DIRDUP	= mkdir -p $(@D)

SRC	= main.c \
		parsing/lexing.c \
		parsing/token_list.c \
		parsing/parsing.c \
		parsing/commands_lst.c \
		parsing/create_cmd.c \
		parsing/lst.c \
		parsing/check_quotes.c \
		parsing/free_minishell.c \
		expand/expand_start.c \
		expand/env_lst.c \
		expand/get_env.c \
		expand/expand_utils.c \
		expand/expand_var.c \
		expand/expand_var2.c \
		expand/expand_quote.c \
		expand/heredoc.c \
		expand/red_treatment.c \
		exec/attributes.c \
		exec/close_and_free.c \
		exec/exec_cmd.c \
		exec/execution.c \
		exec/files.c \
		exec/pathname.c \
		exec/env_.c \
		exec/sign.c \
		exec/is_dir.c \
		builtins/builtins.c \
		builtins/echo.c \
		builtins/cd.c \
		builtins/pwd.c \
		builtins/export.c \
		builtins/export_add.c \
		builtins/export_utils.c \
		builtins/unset.c \
		builtins/env.c \
		builtins/exit.c \
		utils/free_achar.c
		
SRC		:= $(SRC:%=$(SRC_DIR)/%)
OBJ 	:= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
# OBJ 	:= $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) $(LDFLAGS) -o $@ 

$(LIBFT):
	@make -j8 -C libft/ all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
# %.o: %.c $(HEADER)
	$(DIRDUP)
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -f $(OBJ)
	@make -C libft/ clean
	
fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all fclean clean re
