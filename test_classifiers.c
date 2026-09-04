/* test_classifiers.c — throwaway testers for lexer steps 1, 2 and 6.
   Never add this file to the production Makefile.
   One main() may be active at a time: comment the other ones out. */

#include <stdio.h>
#include "minishell.h"

// static const char	*class_name(t_char_class c)
// {
// 	if (c == CLASS_ORDINARY)
// 		return ("ORD");
// 	if (c == CLASS_WHITESPACE)
// 		return ("WS");
// 	if (c == CLASS_QUOTE)
// 		return ("QUOTE");
// 	if (c == CLASS_OPERATOR)
// 		return ("OP");
// 	return ("EXP");
// }

// static const char	*state_name(t_quote_state s)
// {
// 	if (s == STATE_DEFAULT)
// 		return ("DEFAULT");
// 	if (s == STATE_SQUOTE)
// 		return ("SQUOTE");
// 	return ("DQUOTE");
// }

static const char	*type_name(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	if (type == TOKEN_PIPE)
		return ("PIPE");
	if (type == TOKEN_RD_IN)
		return ("RD_IN");
	if (type == TOKEN_RD_OUT)
		return ("RD_OUT");
	if (type == TOKEN_HEREDOC)
		return ("HEREDOC");
	if (type == TOKEN_APPEND)
		return ("APPEND");
	if (type == TOKEN_EOF)
		return ("EOF");
	return ("ERROR");
}

/* ------------------------------------------------------------------ */
/* TESTER 1 — classify_char, 24 cells (PASSED: 0/24 — frozen)         */
/* ------------------------------------------------------------------ */

// int	main(void)
// {
// 	char			chars[8];
// 	t_quote_state	states[3];
// 	t_char_class	expected[3][8];
// 	int				s;
// 	int				i;
// 	int				fails;
// 	t_char_class	got;
// 	const char		*res;
//
// 	chars[0] = '\'';
// 	chars[1] = '"';
// 	chars[2] = '|';
// 	chars[3] = '<';
// 	chars[4] = '>';
// 	chars[5] = '$';
// 	chars[6] = ' ';
// 	chars[7] = 'a';
// 	states[0] = STATE_DEFAULT;
// 	states[1] = STATE_SQUOTE;
// 	states[2] = STATE_DQUOTE;
// 	/* row 0: DEFAULT — quotes are quotes, ops are ops, $ expands */
// 	expected[0][0] = CLASS_QUOTE;
// 	expected[0][1] = CLASS_QUOTE;
// 	expected[0][2] = CLASS_OPERATOR;
// 	expected[0][3] = CLASS_OPERATOR;
// 	expected[0][4] = CLASS_OPERATOR;
// 	expected[0][5] = CLASS_EXPANSION;
// 	expected[0][6] = CLASS_WHITESPACE;
// 	expected[0][7] = CLASS_ORDINARY;
// 	/* row 1: SQUOTE — only the closing ' is special */
// 	expected[1][0] = CLASS_QUOTE;
// 	expected[1][1] = CLASS_ORDINARY;
// 	expected[1][2] = CLASS_ORDINARY;
// 	expected[1][3] = CLASS_ORDINARY;
// 	expected[1][4] = CLASS_ORDINARY;
// 	expected[1][5] = CLASS_ORDINARY;
// 	expected[1][6] = CLASS_ORDINARY;
// 	expected[1][7] = CLASS_ORDINARY;
// 	/* row 2: DQUOTE — " closes, $ still expands, the rest is text */
// 	expected[2][0] = CLASS_ORDINARY;
// 	expected[2][1] = CLASS_QUOTE;
// 	expected[2][2] = CLASS_ORDINARY;
// 	expected[2][3] = CLASS_ORDINARY;
// 	expected[2][4] = CLASS_ORDINARY;
// 	expected[2][5] = CLASS_EXPANSION;
// 	expected[2][6] = CLASS_ORDINARY;
// 	expected[2][7] = CLASS_ORDINARY;
// 	s = 0;
// 	fails = 0;
// 	while (s < 3)
// 	{
// 		i = 0;
// 		while (i < 8)
// 		{
// 			got = classify_char(chars[i], states[s]);
// 			res = "PASS";
// 			if (got != expected[s][i])
// 			{
// 				res = "FAIL";
// 				fails++;
// 			}
// 			printf("state %-7s char [%c] expected %-5s got %-5s -> %s\n",
// 				state_name(states[s]), chars[i],
// 				class_name(expected[s][i]), class_name(got), res);
// 			i++;
// 		}
// 		s++;
// 	}
// 	printf("failures: %d / 24\n", fails);
// 	return (fails != 0);
// }

/* ------------------------------------------------------------------ */
/* TESTER 2 — set_state, 9 cells (PASSED — frozen)                    */
/* ------------------------------------------------------------------ */

// int	main(void)
// {
// 	char			chars[3];
// 	t_quote_state	states[3];
// 	t_quote_state	expected[3][3];
// 	int				s;
// 	int				i;
// 	int				fails;
// 	t_quote_state	got;
// 	const char		*res;
//
// 	chars[0] = '\'';
// 	chars[1] = '"';
// 	chars[2] = 'a';
// 	states[0] = STATE_DEFAULT;
// 	states[1] = STATE_SQUOTE;
// 	states[2] = STATE_DQUOTE;
// 	/* row 0: from DEFAULT  — ' opens single, " opens double, a changes nothing */
// 	expected[0][0] = STATE_SQUOTE;
// 	expected[0][1] = STATE_DQUOTE;
// 	expected[0][2] = STATE_DEFAULT;
// 	/* row 1: from SQUOTE   — ' closes, " is plain text, a changes nothing */
// 	expected[1][0] = STATE_DEFAULT;
// 	expected[1][1] = STATE_SQUOTE;
// 	expected[1][2] = STATE_SQUOTE;
// 	/* row 2: from DQUOTE   — ' is plain text, " closes, a changes nothing */
// 	expected[2][0] = STATE_DQUOTE;
// 	expected[2][1] = STATE_DEFAULT;
// 	expected[2][2] = STATE_DQUOTE;
// 	s = 0;
// 	fails = 0;
// 	while (s < 3)
// 	{
// 		i = 0;
// 		while (i < 3)
// 		{
// 			got = set_state(chars[i], states[s]);
// 			res = "PASS";
// 			if (got != expected[s][i])
// 			{
// 				res = "FAIL";
// 				fails++;
// 			}
// 			printf("from %-7s char [%c] expected %-7s got %-7s -> %s\n",
// 				state_name(states[s]), chars[i],
// 				state_name(expected[s][i]), state_name(got), res);
// 			i++;
// 		}
// 		s++;
// 	}
// 	printf("failures: %d / 9\n", fails);
// 	return (fails != 0);
// }

/* ------------------------------------------------------------------ */
/* TESTER 3 — token list assembly, 10 cases (ACTIVE)                  */
/*                                                                    */
/* Expected output:                                                   */
/*   case 0 []            deliver=1  EOF                              */
/*   case 1 [   ]         deliver=1  EOF                              */
/*   case 2 [ls|wc]       deliver=1  WORD(ls) PIPE WORD(wc) EOF       */
/*   case 3 [echo 'abc]   deliver=0  (no list, unclosed quote)        */
/*   case 4 [echo "a | b"] deliver=1 WORD(echo) WORD("a | b") EOF     */
/*   case 5 [a"bc"d]      deliver=1  WORD(a"bc"d) EOF   (fusion)      */
/*   case 6 [cat < in > out]  WORD RD_IN WORD RD_OUT WORD EOF         */
/*   case 7 [cat << EOF >> out]  WORD HEREDOC WORD APPEND WORD EOF    */
/*   case 8 [ls || wc]    deliver=1  PIPE PIPE adjacency = parser job */
/*   case 9 [   ls   -la   ]  deliver=1  WORD(ls) WORD(-la) EOF       */
/*                                                                    */
/* Known pending bug: cases 0 and 1 crash in deliver_token_list       */
/* because *head is NULL and the EOF node is not made the new head.   */
/* ------------------------------------------------------------------ */

static void	print_list(t_token *head)
{
	while (head)
	{
		printf("  %s[%s]\n", type_name(head->type), head->text);
		head = head->next;
	}
}

int	main(void)
{
	char	*cases[10];
	t_token	*head;
	int		i;
	int		ok;

	cases[0] = "";
	cases[1] = "   ";
	cases[2] = "ls|wc";
	cases[3] = "echo 'abc";
	cases[4] = "echo \"a | b\"";
	cases[5] = "a\"bc\"d";
	cases[6] = "cat < in > out";
	cases[7] = "cat << EOF >> out";
	cases[8] = "ls || wc";
	cases[9] = "   ls   -la   ";
	i = 0;
	while (i < 10)
	{
		head = build_token_list(cases[i]);
		ok = deliver_token_list(&head, cases[i]);
		printf("case %d [%s] deliver=%d\n", i, cases[i], ok);
		print_list(head);
		free_token_list(&head);
		i++;
	}
	return (0);
}
