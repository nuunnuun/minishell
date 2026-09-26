#include "minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

static char	*make_tmp_name(void)
{
	char		*num;
	char		*name;
	static int	counter;

	num = ft_itoa(counter);
	if (num == NULL)
		return (NULL);
	name = ft_strjoin("/tmp/.minishell_heredoc_", num);
	free(num);
	if (name == NULL)
		return (NULL);
	counter++;
	return (name);
}

static int	delim_prepare(const char *raw, char **delim, int *quoted)
{
	size_t	i;
	size_t	j;
	char	*out;

	*quoted = 0;
	if (ft_strchr(raw, '\'') != NULL || ft_strchr(raw, '"') != NULL)
		*quoted = 1;
	out = malloc(ft_strlen(raw) + 1);
	if (out == NULL)
		return (1);
	i = 0;
	j = 0;
	while (raw[i])
	{
		if (raw[i] != '\'' && raw[i] != '"')
			out[j++] = raw[i];
		i++;
	}
	out[j] = '\0';
	*delim = out;
	return (0);
}

static int	capture_loop(int fd_w, const char *delim, int quoted,
		t_shell *shell)
{
	char	*line;

	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
			break ;
		if (write_body_line(fd_w, line, quoted, shell))
		{
			free(line);
			return (1);
		}
		free(line);
		line = readline("> ");
	}
	free(line);
	return (0);
}

static int	body_capture(const char *tmp, const char *delim, int quoted,
		t_shell *shell)
{
	int		fd_w;
	int		fd_r;

	fd_w = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd_w < 0)
		return (-1);
	if (capture_loop(fd_w, delim, quoted, shell))
	{
		close(fd_w);
		return (-1);
	}
	close(fd_w);
	fd_r = open(tmp, O_RDONLY);
	unlink(tmp);
	return (fd_r);
}

int	heredoc_open_fd(const char *raw_delim, t_shell *shell)
{
	char	*tmp;
	char	*delim;
	int		quoted;
	int		fd;

	if (delim_prepare(raw_delim, &delim, &quoted) != 0)
		return (-1);
	tmp = make_tmp_name();
	if (tmp == NULL)
	{
		free(delim);
		return (-1);
	}
	fd = body_capture(tmp, delim, quoted, shell);
	free(delim);
	free(tmp);
	return (fd);
}
