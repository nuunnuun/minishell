# Makefile — throwaway test driver for the parser build.
# NEVER submit this file: the real project Makefile comes later
# with NAME, all, clean, fclean, re and compiles the real sources.
# Usage:  make test   (bundle, compile, run)
#         make clean  (remove tmp/)

CC       = cc
CFLAGS   = -Wall -Wextra -Werror

LIB_SRCS = lexer.c lexer2.c lexer3.c lexer4.c parser.c parser2.c parser3.c parser4.c grammar.c\
	helpers/utils_chars.c \
	helpers/utils_numbers.c \
	helpers/utils_split.c \
	helpers/utils_strings1.c \
	helpers/utils_strings2.c
HDR      = minishell.h
TEST     = test_classifiers.c
BUNDLE   = tmp/minishell_all.c
BIN      = tmp/test_all

test:
	mkdir -p tmp
	for f in $(HDR) $(LIB_SRCS) $(TEST); do cat $$f; echo; done > $(BUNDLE)
	$(CC) $(CFLAGS) -I. $(BUNDLE) -o $(BIN)
	$(BIN)

clean:
	rm -rf tmp

.PHONY: test clean
