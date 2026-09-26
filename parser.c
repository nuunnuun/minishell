#include "minishell.h"

static int  token_amount(t_token *token_list)
{
    t_token   *current;
    int len;

    len = 0;
    current = token_list;
    while (current->next != NULL && !(current->type == TOKEN_PIPE ||
    current->type == TOKEN_EOF))
    {
        if (is_redirect_type(current->type))
            current = current->next;
        else
            len++;
        current = current->next;
    }
    return (len);
}

static t_command    *alloc_command(t_token **list)
{
    t_command   *command;
    int         len;

    command = malloc(sizeof(t_command));
    if (command == NULL)
        return (NULL);
    len = token_amount(*list);
    command->argv = ft_calloc(len + 1, sizeof(char *));
    if (command->argv == NULL)
    {
        free(command);
        return (NULL);
    }
    command->redirs = NULL;
    command->pipe = 0;
    command->next = NULL;
    return (command);
}

static t_redirect  *alloc_redirect(t_token_type redirect_type, t_token *target)
{
    t_redirect *redirect;
 
    redirect = ft_calloc(1, sizeof(t_redirect));
    if (redirect == NULL)
        return (NULL);
    redirect->rd_type = redirect_type;
    redirect->target = ft_strdup(target->text);
    if (redirect->target == NULL)
    {
        free(redirect);
        return (NULL);
    }
    redirect->fd = -1;
    redirect->next = NULL;
    return (redirect);
}

int add_redirect(t_command *command, t_token_type redirect_type, t_token *target)
{
    t_redirect *redirect;
    t_redirect *tail;

    redirect = alloc_redirect(redirect_type, target);
    if (redirect == NULL)
        return (0);
    if (command->redirs == NULL)
        command->redirs = redirect;
    else
    {
        tail = command->redirs;
        while (tail->next)
            tail = tail->next;
        tail->next = redirect;
    }
    return (1);
}

t_command   *build_command(t_token **current)
{
    t_command   *command;
    int         i;

    i = 0;
    command = alloc_command(current);
    if (command == NULL)
        return (NULL);
    while ((*current) != NULL && (*current)->type != TOKEN_EOF
    && (*current)->type != TOKEN_PIPE)
    {
        if (!build_redirect_or_argv(command, current, &i))
        {
            free_one_command(command);
            return (NULL);
        }
    }
    if ((*current) != NULL && (*current)->type == TOKEN_PIPE)
        build_pipe(command, current);
    return (command);
}



