NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

SRCS = ft_atoi.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isdigit.c \
	ft_itoa.c ft_putendl_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
	ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c ft_strtrim.c \
	ft_substr.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
