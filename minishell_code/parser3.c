#include "minishell.h"

int  is_redirect_type(t_token_type type)
{
    if (type == TOKEN_RD_IN || type == TOKEN_RD_OUT 
        || type == TOKEN_APPEND || type == TOKEN_HEREDOC)
        return (1);
    return (0);
}

static int build_redirect(t_command *command, t_token **current)
{
    t_token *target;

    target = (*current)->next;
    if (!add_redirect(command, (*current)->type,target))
                return (0);
    *current = target->next;
    return (1);
}

static int build_argv(t_command *command, t_token **current, int *i)
{
    command->argv[*i] = ft_strdup((*current)->text);
    if (command ->argv[*i]== NULL)
        return (0);
    *current = (*current)->next;
    (*i)++;
    return (1);
}

void    build_pipe(t_command *command, t_token **current)
{
    command->pipe = 1;
    *current = (*current)->next;
}

int build_redirect_or_argv(t_command *command, t_token **current, int *i)
{
    if (is_redirect_type((*current)->type))
    {
        if (!build_redirect(command, current))
            return (0);
    }
    else
    {
        if(!build_argv(command, current, i))
            return (0);
    }
    return (1);
}
