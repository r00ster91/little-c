CFLAGS_WARNINGS=-Wall -Wextra -Wpedantic -Werror -Wshadow -Wno-unused-function
CLFAGS=$(CFLAGS_WARNINGS) -std=c99 -lm

build:
	cc main.c grid.c helpers.c -o tictactoe $(CLFAGS)

run: build
	./tictactoe
