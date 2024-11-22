# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/25 13:27:38 by jalombar          #+#    #+#              #
#    Updated: 2024/09/25 13:27:38 by jalombar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -I -g -Wall -Werror -Wextra
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft -g
RL_FLAGS = -L/path/to/readline-8.2/.libs -lreadline
SRCS = minishell.c $(EXEC) $(PARSING) $(TOKEN) $(EXPAND) testing/testing_funcs.c
EXEC = source/execution/builtins/cd.c \
		source/execution/builtins/echo.c \
		source/execution/builtins/env.c \
		source/execution/builtins/exit.c \
		source/execution/builtins/export.c \
		source/execution/builtins/pwd.c \
		source/execution/builtins/unset.c \
		source/execution/bin.c \
		source/execution/env.c \
		source/execution/error.c \
		source/execution/exec.c \
		source/execution/free.c \
		source/execution/pipe.c \
		source/execution/redirections.c \
		source/execution/heredoc.c \
		source/execution/signals.c \
		source/execution/subshell.c \
		source/execution/utils.c \
		source/execution/var.c
PARSING = source/parsing/parse.c \
			source/parsing/parsing_nodes.c \
			source/parsing/parsing_utils.c \
			source/parsing/parsing_movement.c \
			source/parsing/parsing_output.c \
			source/parsing/parsing_cleanup.c
TOKEN = source/tokenizing/token_making.c \
		source/tokenizing/token_utils.c \
		source/tokenizing/token_quote_handling.c \
		source/tokenizing/tokenize.c
EXPAND = source/expanding/expand.c \
		source/expanding/expanding_utils.c \
		source/expanding/expanding_shell_vars.c
HEADER = minishell.h
NAME = minishell
LIBFT_PATH = libraries/libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	@$(CC) $(FLAGS) -o $@ $(SRCS) $(LIBFT_FLAGS) $(RL_FLAGS)

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_PATH)

clean:
	@$(MAKE) -s -C $(LIBFT_PATH) clean

fclean: clean
	@$(MAKE) -s -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all
