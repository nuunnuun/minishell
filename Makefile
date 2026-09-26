NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

READLINE_PREFIX = $(shell brew --prefix readline 2>/dev/null)

INCLUDES = -I.

ifneq ($(READLINE_PREFIX),)
INCLUDES += -I$(READLINE_PREFIX)/include
READLINE_FLAGS = -L$(READLINE_PREFIX)/lib -lreadline
else
READLINE_FLAGS = -lreadline
endif

SRCS = main.c \
       link_command.c \
       link_redirect.c \
       link_expand.c \
       signals.c \
       environment.c \
       environment_update.c \
       environment_unset.c \
       executor.c \
       executor_child.c \
       executor_builtin_redir.c \
       executor_commands.c \
       executor_path.c \
       redirection.c \
       pipeline.c \
       pipeline_child.c \
       builtin_echo.c \
       builtin_dispatch.c \
       builtin_pwd.c \
       builtin_env.c \
       builtin_identifier.c \
       builtin_unset.c \
       builtin_cd.c \
       builtin_export.c \
       builtin_export_print.c \
       builtin_exit.c \
       lexer.c \
       lexer2.c \
       lexer3.c \
       lexer4.c \
       parser.c \
       parser2.c \
       parser3.c \
       parser4.c \
       grammar.c \
       expander.c \
       expander_dollar.c \
       heredoc.c \
       utils_chars.c \
       utils_numbers.c \
       utils_split.c \
       utils_strings1.c \
       utils_strings2.c

OBJS = $(SRCS:.c=.o)
HDR = minishell.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(READLINE_FLAGS) -o $(NAME)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
