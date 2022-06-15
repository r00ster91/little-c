#include <stdio.h>
#include <stdlib.h>
#include <math.h> // again, this brings in all declarations, not the definitions, for that we link with libm (find `-lm` in the Makefile)
#include "grid.h"

struct Grid new_grid(const unsigned size) {
    unsigned i, len;

    // considering that currently the grid size is always 9 (3 * 3),
    // this could've been an array but I decided to leave it as-is
    len = get_grid_cells_len(size);
    enum Cell *cells = malloc(len * sizeof(enum Cell));
    for (i = 0; i < len; ++i)
        cells[i] = CELL_EMPTY;

    struct Grid grid = {
        .size = size,
        .cells = cells,
    };

    return grid;
}

void free_grid(const struct Grid *grid) {
    free(grid->cells);
}

// don't bother storing this in the `struct`, it takes no time to compute on demand
unsigned get_grid_cells_len(const unsigned size) {
    return pow(size, 2);
}

// here we pass the `struct` by value which means it will be copied into the function's stack so that we can work with it (in this case we only read from it)
// on other occassions to avoid an expensive copy of a bigger struct, it might be more efficient to pass by reference (a pointer)
void print_grid(const struct Grid grid) {
    unsigned i, j, len;

    len = get_grid_cells_len(grid.size);
    for (i = 0; i < len; ++i) {
        if (i == 0) {
            putchar(' ');
        } else {
            if (i % grid.size == 0) {
                putchar('\n');
                for (j = 0; j < (grid.size * 4) - 1; ++j)
                    putchar('-');
                printf("\n ");
            } else {
                printf(" | ");
            }
        }

        enum Cell cell = grid.cells[i];
        switch (cell) {
            case CELL_EMPTY:
                printf("%d", i + 1);
                break;
            case CELL_NOUGHT:
            case CELL_CROSS:
                putchar(get_cell_char(cell));
                break;
        }
    }
}

// the `const` for every parameter is probably not incredibly important as we're taking in a copy from outside anyway
// but I think it might still be good style to default to immutability
char get_cell_char(const enum Cell cell) {
    switch (cell) {
        case CELL_NOUGHT: return 'O';
        case CELL_CROSS: return 'X';
        default:
            // see comment in main.c
            puts("panic: invalid cell variant");
            exit(1);
    }
}

// `static` here simply makes the function private to the current file (translation unit)
static enum State cell_to_state(const enum Cell cell) {
    switch (cell) {
        case CELL_NOUGHT: return STATE_NOUGHT_WON;
        case CELL_CROSS: return STATE_CROSS_WON;
        default:
            // see comment in main.c
            puts("panic: invalid cell variant");
            exit(1);
    }
}

/*
 * Checks whether the specified cells all match `cell`.
 */
static _Bool check(const struct Grid grid, _Bool *grid_specifier, enum Cell cell) {
    unsigned i;

    for (i = 0; i < get_grid_cells_len(grid.size); ++i) {
        if (grid_specifier[i] == 1 && grid.cells[i] != cell)
            return 0;
    }

    return 1;
}

enum State check_grid(const struct Grid grid) {
    unsigned i;
    enum Cell cell = CELL_NOUGHT;

    // check horizontally
    if (check(grid, (_Bool []){ 1, 1, 1,
                                0, 0, 0,
                                0, 0, 0, }, cell))
        return cell_to_state(cell);
    if (check(grid, (_Bool []){ 0, 0, 0,
                                1, 1, 1,
                                0, 0, 0, }, cell))
        return cell_to_state(cell);
    if (check(grid, (_Bool []){ 0, 0, 0,
                                0, 0, 0,
                                1, 1, 1, }, cell))
        return cell_to_state(cell);

    // check vertically
    if (check(grid, (_Bool []){ 1, 0, 0,
                                1, 0, 0,
                                1, 0, 0, }, cell))
        return cell_to_state(cell);
    if (check(grid, (_Bool []){ 0, 1, 0,
                                0, 1, 0,
                                0, 1, 0, }, cell))
        return cell_to_state(cell);
    if (check(grid, (_Bool []){ 0, 0, 1,
                                0, 0, 1,
                                0, 0, 1, }, cell))
        return cell_to_state(cell);

    // check diagonally
    if (check(grid, (_Bool []){ 1, 0, 0,
                                0, 1, 0,
                                0, 0, 1, }, cell))
        return cell_to_state(cell);
    if (check(grid, (_Bool []){ 0, 0, 1,
                                0, 1, 0,
                                1, 0, 0, }, cell))
        return cell_to_state(cell);

    _Bool draw = 1;
    for (i = 0; i < get_grid_cells_len(grid.size); ++i) {
        if (grid.cells[i] == CELL_EMPTY) {
            draw = 0;
            break;
        }
    }
    if (draw) return STATE_DRAW;

    return STATE_CONTINUE;
}
