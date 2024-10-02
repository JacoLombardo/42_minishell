SRCS	= c.c tokenizer.c token_making.c token_utils.c
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
	$(info Linking $(NAME)...)
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)
	$(info Done!)
	
%.o: %.c
	$(info Building $@...)
	@$(CC) $(CFLAGS) $(LFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@make -s -C includes/libft clean
	$(info Removed!)
fclean: clean
	@rm -f $(NAME)
	@make -s -C includes/libft fclean

re:	fclean all
