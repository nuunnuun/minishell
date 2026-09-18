#include "minishell.h"

int    is_whitespace(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}

int    is_operator(char c)
{
    if (c == '<' || c == '>' || c == '|')
        return (1);
    return (0);
}

static int    is_quote(char c)
{
    if (c == '"' || c == '\'')
        return (1);
    return (0);
}

t_char_class classify_char(char c, t_quote_state state)
{
    if (state == STATE_SQUOTE || state == STATE_DQUOTE)
    {
        if (c == '\'' && state == STATE_SQUOTE)
           return (CLASS_QUOTE);
        if (c == '$' && state == STATE_DQUOTE)
            return (CLASS_EXPANSION);
        if (c == '"' && state == STATE_DQUOTE)
            return (CLASS_QUOTE);
        return (CLASS_ORDINARY);
    }
    if (is_whitespace(c))
        return (CLASS_WHITESPACE);
    if (is_operator(c))
        return (CLASS_OPERATOR);
    if (is_quote(c))
        return (CLASS_QUOTE);
    if (c == '$')
        return (CLASS_EXPANSION);
    else
        return (CLASS_ORDINARY);
}

t_quote_state   set_state(char c, t_quote_state state)
{
    if (state == STATE_DEFAULT && (c == '\'' || c == '"'))
    {
        if (c == '\'')
            return (STATE_SQUOTE);
        return (STATE_DQUOTE);
    }
    if (state == STATE_SQUOTE && c == '\'')
        return (STATE_DEFAULT);
    if (state == STATE_DQUOTE && c == '"')
        return (STATE_DEFAULT);
    return (state);
}