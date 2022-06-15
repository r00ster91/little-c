// headers includes the prototypes/declarations of functions etc.

/* this is one way to avoid problems when `#include`ing the same file multiple times.
 * this is also what the Linux kernel does (e.g. https://github.com/torvalds/linux/blob/7b58b82b86c8b65a2b57a4c6cb96a460654f9e09/tools/perf/util/block-range.h#L3)
 * NOTE: an alternative is `#pragma once` but this kind of include guard seems to work in more cases than `#pragma once` */
#ifndef GRID_H
#define GRID_H

enum Cell { // this will have to be used with `enum` in front of `Cell` (like for `struct`s)
    CELL_EMPTY,
    CELL_NOUGHT, // these will be global identifiers so we use a prefix to avoid collisions
    CELL_CROSS, // these will be global identifiers so we use a prefix to avoid collisions
}; // why does specifiying an identifier here give a "multiple definition of" error?

// the following would allow us to write only `Cell`
//typedef enum Cell Cell;

// I expect this to have a size of 4 + 8 = 12 bytes on most 64-bit machines
struct Grid {
    const unsigned size; // `const` because this won't change later
    enum Cell *cells;
};

enum State {
    STATE_NOUGHT_WON,
    STATE_CROSS_WON,
    STATE_DRAW,
    STATE_CONTINUE,
};

// currently I don't really like `typedef`s because I like it when I immediately see whether I'm dealing with an `enum` or a `struct ` etc.
// so I didn't use them here

struct Grid new_grid(const unsigned size);
void free_grid(const struct Grid *grid);
enum State check_grid(const struct Grid grid);
unsigned get_grid_cells_len(const unsigned size);
void print_grid(const struct Grid);
char get_cell_char(const enum Cell);

#endif /* GRID_H */
