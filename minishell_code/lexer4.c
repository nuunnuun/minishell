#include "minishell.h"

t_token *add_token(t_token **head, t_token new_token)
{
    t_token *node;
    t_token *current;

    node = malloc(sizeof(t_token));
    if (!node)
        return (NULL);
    *node = new_token;
    node->next = NULL;
    if (*head == NULL)
    {
        *head = node;
        return (node);
    }
    current = *head;
    while (current->next != NULL)
        current = current->next;
    current->next = node;
    return (node);
}

void free_token_list(t_token **head)
{
    t_token *next;

    while (*head)
    {
        next = (*head)->next;
        free((*head)->text);
        free (*head);
        (*head) = next;
    }
}

void    deliver_token_list_helper(t_token **head, t_token *eof_token)
{
    t_token *current;

    if (*head == NULL)
        *head = eof_token;
    else
    {
        current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = eof_token;
    }
}