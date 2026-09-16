
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

typedef struct s_redirect
{
    int                 rd_type;
    char                *target;
    int                 fd;
    struct s_redirect    *next;
}   t_redirect;

typedef struct s_command
{
    char                **argv;
    int                 pipe;
    t_redirect          *redirs; 
    struct s_command    *next;
    
}   t_command;

/* functions lexer */

t_char_class    classify_char(char c, t_quote_state state);
t_quote_state   set_state(char c, t_quote_state state);
t_token         build_word(const char *line, int start_index, int *end_index);
t_token         build_operator(const char *line, int start_index);
t_token	        *build_token_list(const char *line);
t_token         *add_token(t_token **head, t_token new_token);
void            deliver_token_list_helper(t_token **head, t_token *eof_token);
void	        free_token_list(t_token **head);
int             is_operator(char c);
int             is_whitespace(char c);
int             operator_len(t_token_type type);
int	            empty_line_check(const char *line);
int             deliver_token_list(t_token **head, const char *line);

/* functions parser */

t_command       *build_command_list(t_token *tokens);
t_command       *build_command(t_token **current);
void            free_command_list(t_command *list);
void            free_one_command(t_command *command);
void            build_pipe(t_command *command, t_token **current);
int             build_redirect_or_argv(t_command *command, t_token **current, int *i);
int             add_redirect(t_command *command, t_token_type redirect_type, t_token *target);
int             is_redirect_type(t_token_type type);
t_command       *parse(const char *line, int *status);

/*functions grammar*/

int             check_grammar(t_token *tokens);

/* functions helpers */

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