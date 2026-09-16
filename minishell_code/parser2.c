#include "minishell.h"

void    free_command_list(t_command *list)
{
    t_command   *current;

    while (list)
    {
        current = list;
        list = list->next;
        free_one_command(current);
    }
}

static void    free_redirects(t_redirect *redirect)
{
    t_redirect  *current;

    while (redirect)
    {
        current = redirect;
        redirect = redirect->next;
        free(current->target);
        free(current);
    }
}

void    free_one_command(t_command *command)
{
    int         i;

    i = 0;
    free_redirects(command->redirs);
    while (command->argv[i])
    {
        free(command->argv[i]);
        i++;
    }
    free(command->argv);
    free(command);
}

static void attach_command(t_command **command_list, t_command *command)
{
    t_command   *current;

    current = *command_list;
    if (current == NULL)
    {
        *command_list = command;
        return ;
    }
    while (current->next != NULL)
        current = current->next;
    current->next = command;
}

t_command   *build_command_list(t_token *tokens)
{
    t_command   *command_list;
    t_command   *command;
    t_token     *current;

    command_list = NULL;
    if (tokens == NULL)
        return (NULL);
    current = tokens;
    while (current != NULL && current->type != TOKEN_EOF)
    {
        command = build_command(&current);
        if (command == NULL)
        {
            free_command_list(command_list);
            return (NULL);
        }
        attach_command(&command_list, command);
    }
    return (command_list);
}

