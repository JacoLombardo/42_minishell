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
SRCS = minishell.c \
		source/execution/builtins.c \
		source/execution/builtins2.c \
		source/execution/env.c \
		source/execution/exec.c \
		source/execution/free.c \
		source/execution/operators.c \
		source/execution/pipe.c \
		source/execution/redirections.c \
		source/execution/signals.c \
		source/execution/utils.c
HEADER = minishell.h
NAME = minishell
LIBFT_PATH = libraries/libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	$(CC) $(FLAGS) -o $@ $(SRCS) $(LIBFT_FLAGS) $(RL_FLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

clean:
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all
