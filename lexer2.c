#include "minishell.h"

static int	find_word_boundry(char *line, int start_index,
				t_quote_state *state);
static char	*extract_word(char *line, int start_index, int end_index);

t_token build_word(char *line, int start_index, int *end_index)
{
    t_quote_state   state;
    t_token         token;
    char            *word;
    
    token.text = NULL;
    token.next = NULL;
    *end_index = find_word_boundry(line, start_index, &state);
    if (state != STATE_DEFAULT)
        token.type = TOKEN_ERROR;
    else
    {
        word = extract_word(line, start_index, *end_index);
        token.type = TOKEN_WORD;
        token.text = word;
    }
    return (token);
}

static int find_word_boundry(char *line, int start_index, t_quote_state *state)
{
    t_char_class    character;
    t_quote_state   current_state;

    current_state = STATE_DEFAULT;
    while (line[start_index])
    {
        current_state = set_state(line[start_index], current_state);
        character = classify_char(line[start_index], current_state);
        if (current_state == STATE_DEFAULT && (character == CLASS_WHITESPACE
            || character == CLASS_OPERATOR))
            break;
        start_index++;
    }
    *state = current_state;
    return (start_index - 1);
}

static char *extract_word(char *line, int start_index, int end_index)
{
    int len;
    char *word;

    len = end_index - start_index + 1;
    word = ft_substr(line, start_index, len);
    return (word);
}

t_token build_operator(char *line, int start_index)
{
    t_token token;

    token.text = NULL;
    token.next = NULL;
    if (line[start_index] == '|')
        token.type = TOKEN_PIPE;
    else if (line[start_index] == '>' && line[start_index + 1] == '>')
        token.type = TOKEN_APPEND;
    else if (line[start_index] == '>')
        token.type = TOKEN_RD_OUT;
    else if (line[start_index] == '<' && line[start_index + 1] == '<')
        token.type = TOKEN_HEREDOC;
    else
        token.type = TOKEN_RD_IN;
    return (token);
}

int operator_len(t_token_type type)
{
    if (type == TOKEN_APPEND || type == TOKEN_HEREDOC)
        return (2);
    return (1);
}