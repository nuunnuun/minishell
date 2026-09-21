
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

SRCS = src/main.c \
       src/environment.c \
       src/environment_update.c \
       src/executor_path.c \
       src/executor.c \
       src/executor_child.c \
       src/executor_dispatch.c \
       src/executor_builtin_redir.c \
       src/executor_commands.c \
       src/redirection.c \
       src/pipeline.c \
       src/pipeline_child.c \
       src/environment_unset.c \
       src/builtins/builtin_echo.c \
       src/builtins/builtin_dispatch.c \
       src/builtins/builtin_pwd.c \
       src/builtins/builtin_env.c \
       src/builtins/builtin_identifier.c \
       src/builtins/builtin_unset.c \
       src/builtins/builtin_cd.c \
       src/builtins/builtin_export.c \
       src/builtins/builtin_export_print.c \
       src/builtins/builtin_exit.c

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
