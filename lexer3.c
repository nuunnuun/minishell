#include "minishell.h"

static t_token *add_token(t_token **head, t_token new_token)
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


static int add_word_token(t_token **head, char *line, int *start_index)
{
    int end_index;
    t_token token;

    token = build_word(line, *start_index, &end_index);
    if (token.type == TOKEN_ERROR)
    {
        free_token_list(head);
        return (0);
    }
    else
    {
        if (!add_token(head, token))
        {
            free_token_list(head);
            return (0);
        }
    }
    *start_index = end_index + 1; 
    return (1);
}

static int  add_operator_token(t_token **head, char *line, int *start_index)
{
    t_token token;

    token = build_operator(line, *start_index);
    if (!add_token(head, token))
    {
        free_token_list(head);
        return (0);
    }
    *start_index += operator_len(token.type);
    return (1);
}

t_token *build_token_list(char *line)
{
    int start_index;
    t_token *head;

    head = NULL;
    start_index = 0;
    while (line[start_index])
    {
        if (is_whitespace(line[start_index]))
            start_index++;
        else if (is_operator(line[start_index]))
            add_operator_token(&head, line, &start_index);
        else
        {
            if (!add_word_token(&head, line, &start_index))
                return (NULL);
        }
    }
    return (head);
}
