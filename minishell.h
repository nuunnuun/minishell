
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef enum e_char_class
{
	CLASS_ORDINARY = 0,
	CLASS_WHITESPACE,
	CLASS_QUOTE,
	CLASS_OPERATOR,
	CLASS_EXPANSION
}	t_char_class;

typedef enum e_quote_state
{
	STATE_DEFAULT = 0,
	STATE_SQUOTE,
	STATE_DQUOTE
}	t_quote_state;

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
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*text;
	struct s_token		*next;
}	t_token;

typedef struct s_redirect
{
	int					rd_type;
	char				*target;
	int					fd;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command
{
	char				**argv;
	int					pipe;
	t_redirect			*redirs;
	struct s_command	*next;
}	t_command;

typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redirection
{
	t_redir_type			type;
	char					*filename;
	int						fd;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_exec_cmd
{
	char				**argv;
	t_redirection		*redirections;
	struct s_exec_cmd	*next;
}	t_exec_cmd;

typedef struct s_pipeline
{
	int		input_fd;
	pid_t	last_pid;
	int		child_count;
}	t_pipeline;

typedef struct s_shell
{
	char	**env;
	int		last_status;
	int		should_exit;
	int		exit_status;
}	t_shell;

extern volatile sig_atomic_t	g_signal;

t_char_class	classify_char(char c, t_quote_state state);
t_quote_state	set_state(char c, t_quote_state state);
t_token			build_word(const char *line, int start_index, int *end_index);
t_token			build_operator(const char *line, int start_index);
t_token			*build_token_list(const char *line);
t_token			*add_token(t_token **head, t_token new_token);
void			deliver_token_list_helper(t_token **head, t_token *eof_token);
void			free_token_list(t_token **head);
int				is_operator(char c);
int				is_whitespace(char c);
int				operator_len(t_token_type type);
int				empty_line_check(const char *line);
int				deliver_token_list(t_token **head, const char *line);

t_command		*parse(const char *line, int *status);
t_command		*build_command_list(t_token *tokens);
t_command		*build_command(t_token **current);
void			free_command_list(t_command *list);
void			free_one_command(t_command *command);
void			build_pipe(t_command *command, t_token **current);
int				build_redirect_or_argv(t_command *command,
					t_token **current, int *i);
int				add_redirect(t_command *command, t_token_type redirect_type,
					t_token *target);
int				is_redirect_type(t_token_type type);
int				check_grammar(t_token *tokens);

char			*add_str(char *s1, const char *s2);
char			*expand_word(const char *line, int status, char **env);
char			*expand_dollar(const char *line, int *i, int status, char *word,
					char **env);
int				is_bare_expansion(const char *raw);
int				heredoc_open_fd(const char *raw_delim, t_shell *shell);
int				write_body_line(int fd_w, char *line, int quoted,
					t_shell *shell);

t_exec_cmd		*convert_commands(t_command *cmds);
int				convert_redirs(t_exec_cmd *dst, t_redirect *src);
void			free_exec_cmd_list(t_exec_cmd *list);
void			close_heredoc_fds(t_command *cmds);
int				expand_commands(t_command *cmds, t_shell *shell);

char			**env_copy(char **envp);
void			env_free(char **env);
char			*env_get(char **env, char *name);
void			shell_init_env(t_shell *shell);
int				is_builtin(char *name);
int				execute_builtin(t_shell *shell, char **argv);
int				builtin_echo(t_shell *shell, char **argv);
int				builtin_pwd(t_shell *shell, char **argv);
int				builtin_env(t_shell *shell, char **argv);
int				builtin_cd(t_shell *shell, char **argv);
int				builtin_export(t_shell *shell, char **argv);
int				builtin_unset(t_shell *shell, char **argv);
int				builtin_exit(t_shell *shell, char **argv);
int				env_set(t_shell *shell, char *name, char *value);
void			env_unset(t_shell *shell, char *name);
int				is_valid_env_name(char *name);
int				print_export(char **env);
char			*resolve_command_path(t_shell *shell, char *command);
int				execute_external(t_shell *shell, char **argv);
int				executor_wait_child(pid_t pid);
void			executor_run_child(t_shell *shell, char **argv, char *path);
int				apply_redirections(t_redirection *redirection);
int				execute_builtin_redir(t_shell *shell, t_exec_cmd *command);
int				execute_pipeline(t_shell *shell, t_exec_cmd *command);
int				execute_commands(t_shell *shell, t_exec_cmd *command);
void			pipeline_run_child(t_shell *shell, t_exec_cmd *command,
					int input_fd, int pipe_fd[2]);
void			signals_prompt(void);
void			signals_parent_wait(void);
void			signals_child_default(void);

size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_split(char const *s, char c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_itoa(int n);
void			*ft_calloc(size_t count, size_t size);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
int				ft_atoi(const char *nptr);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_isdigit(int c);
int				skip_bare_name(const char *raw, int i);

#endif
