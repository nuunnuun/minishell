
NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

READLINE_PREFIX = $(shell brew --prefix readline 2>/dev/null)

INCLUDES = -Iinclude -Ilibft

ifneq ($(READLINE_PREFIX),)
INCLUDES += -I$(READLINE_PREFIX)/include
READLINE_FLAGS = -L$(READLINE_PREFIX)/lib -lreadline
else
READLINE_FLAGS = -lreadline
endif

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_SRC = $(wildcard $(LIBFT_DIR)/*.c) \
			$(LIBFT_DIR)/libft.h \
			$(LIBFT_DIR)/Makefile

SRCS = src/main.c \
       src/signals.c \
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
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_FLAGS) -o $(NAME)

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
