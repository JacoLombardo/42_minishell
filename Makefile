SRCS	= c.c \
		expanding/expand.c expanding/ft_charjoin.c \
		tokenizing/token_making.c tokenizing/token_utils.c tokenizing/tokenize.c \
		parsing/parse.c
OBJS	= $(SRCS:%.c=%.o)
NAME	= test
CC	= cc # add flags
CFLAGS	= -g -I.

# libft
LIBFT = includes/libft/libft.a

# linker flags
LIBFT_FLAGS = -Lincludes/libft -lft
LFLAGS = $(LIBFT_FLAGS)

all:	$(NAME)

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
