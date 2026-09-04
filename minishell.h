
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_char_class
{
    CLASS_ORDINARY = 0,
    CLASS_WHITESPACE,
    CLASS_QUOTE,
    CLASS_OPERATOR,
    CLASS_EXPANSION
}   t_char_class;

typedef enum e_quote_state
{
    STATE_DEFAULT = 0,
    STATE_SQUOTE,
    STATE_DQUOTE
}   t_quote_state;

typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_RD_IN,
    TOKEN_RD_OUT,
    TOKEN_HEREDOC,
    TOKEN_APPEND,
    TOKEN_EOF,
    TOKEN_ERROR
}   t_token_type;

typedef struct s_token
{
    t_token_type    type;
    char *text;
    struct s_token *next;
}   t_token;

/* functions lexer */

t_char_class    classify_char(char c, t_quote_state state);
t_quote_state   set_state(char c, t_quote_state state);
t_token         build_word(char *line, int start_index, int *end_index);
t_token         build_operator(char *line, int start_index);
t_token	        *build_token_list(char *line);
void	        free_token_list(t_token **head);
int             is_operator(char c);
int             is_whitespace(char c);
int             operator_len(t_token_type type);
int	            empty_line_check(char *line);
int             deliver_token_list(t_token **head, char *line);
int             empty_line_check(char *line);

/* helpers */
size_t	        ft_strlen(const char *s);
char	        *ft_strdup(const char *s);
char	        *ft_strchr(const char *s, int c);
char	        *ft_strjoin(char const *s1, char const *s2);
char	        **ft_split(char const *s, char c);
char	        *ft_substr(char const *s, unsigned int start, size_t len);
char	        *ft_strtrim(char const *s1, char const *set);
char	        *ft_itoa(int n);
void	        *ft_calloc(size_t count, size_t size);
void	        ft_putstr_fd(char *s, int fd);
void	        ft_putendl_fd(char *s, int fd);
int		        ft_atoi(const char *nptr);
int		        ft_strncmp(const char *s1, const char *s2, size_t n);
int		        ft_isalpha(int c);
int		        ft_isalnum(int c);
int		        ft_isdigit(int c);

#endif