#include "minishell.h"

static void    check_word(t_token *token, int *expect_target, int *expect_command)
{
    if (token->type == TOKEN_WORD)
    {
        if (*expect_target)
            *expect_target = 0;
        else
            *expect_command = 0;
    }
}

static int check_operator(t_token *token, int *expect_target, int *expect_command)
{
    if (token->type == TOKEN_PIPE)
    {
        if (*expect_command)
            return (1);
        if (*expect_target)
            return (1);
        *expect_command = 1;
    }
    if (is_redirect_type(token->type))
    {
        if (*expect_target)
            return (1);
        *expect_target = 1;
    }
    return (0);
}

static int check_eof(int *expect_target, int *expect_command)
{
    if (*expect_command)
        return (1);
    if (*expect_target)
        return (1);
    return (0);
}

int check_grammar(t_token *tokens)
{
    t_token *current;
    int     expect_command;
    int     expect_target;

    current = tokens;
    expect_command = 1;
    expect_target = 0;
    if (current->type == TOKEN_EOF)
        return (0);
    while (current)
    {
        check_word(current, &expect_target, &expect_command);
        if (check_operator(current, &expect_target, &expect_command))
            return (1);
        if (current->type == TOKEN_EOF)
            return (check_eof(&expect_target, &expect_command));
        current = current->next;
    }
    return (0);
}