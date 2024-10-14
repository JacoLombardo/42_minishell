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
FLAGS = -Wall -Werror -Wextra
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft
RL_FLAGS = -L/path/to/readline-8.2/.libs -lreadline
SRCS = minishell.c $(EXEC) $(PARSINg) $(TOKEN) $(EXPAND) testing/testing_funcs.c
EXEC = source/execution/builtins.c \
		source/execution/builtins2.c \
		source/execution/env.c \
		source/execution/exec.c \
		source/execution/free.c \
		source/execution/operators.c \
		source/execution/pipe.c \
		source/execution/redirections.c \
		source/execution/signals.c \
		source/execution/utils.c
PARSING = source/parsing/parse.c \
			source/parsing/parsing_nodes.c \
			source/parsing/parsing_utils.c \
			source/parsing/parsing_movement.c \
			source/parsing/parsing_output.c
TOKEN = source/tokenizing/token_making.c \
		source/tokenizing/token_utils.c \
		source/tokenizing/tokenize.c
EXPAND = source/expanding/expand.c \
			source/expanding/ft_charjoin.c
HEADER = minishell.h
NAME = minishell
LIBFT_PATH = libraries/libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	$(CC) $(FLAGS) -o $@ $(SRCS) $(LIBFT_FLAGS) $(RL_FLAGS)

$(LIBFT):
	$(info Building libft...)
	@make -s -C includes/libft
	
$(NAME): $(LIBFT) $(OBJS)
	$(info Building $(NAME)...)
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)
	$(info Done!)
	
%.o: %.c
	@$(CC) $(CFLAGS) $(LFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@make -s -C includes/libft clean
	$(info Removed!)
fclean: clean
	@rm -f $(NAME)
	@make -s -C includes/libft fclean

re:	fclean all
