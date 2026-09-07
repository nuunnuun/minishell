
NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

INCLUDES = -Iinclude -Ilibft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_SRC = $(wildcard $(LIBFT_DIR)/*.c) \
			$(LIBFT_DIR)/libft.h \
			$(LIBFT_DIR)/Makefile

SRCS = src/main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT): $(LIBFT_SRC)
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c include/minishell.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
