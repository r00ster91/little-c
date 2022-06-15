#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "helpers.h"

int main() {
    puts("Please enter the grid size.");
    unsigned grid_size = read_number(3, "Sorry, grid sizes greater than 3 are not supported.");
    if (grid_size != 3) {
        puts("Sorry, currently only grid size 3 is supported.");
        return 1;
    }
    struct Grid grid = new_grid(grid_size);

    enum Cell mark = CELL_NOUGHT;
    while(1) {
        printf("It's the turn of the player with mark %c!\n", get_cell_char(mark));
        print_grid(grid);
        putchar('\n');
        unsigned cell_index = read_number(get_grid_cells_len(grid.size), "That field doesn't exist!") - 1;
        grid.cells[cell_index] = mark;

        enum State state = check_grid(grid);
        printf("%d\n", state);
        switch (state) {
            case STATE_NOUGHT_WON: // fall through
            case STATE_CROSS_WON:
                printf("The player with mark %c won the game!\n", get_cell_char(mark));
                print_grid(grid);
                putchar('\n');
                goto exit;
            case STATE_DRAW:
                printf("It's a draw!\n");
                goto exit;
            case STATE_CONTINUE:
                break;
        }

        switch (mark) {
            case CELL_NOUGHT:
                mark = CELL_CROSS;
                break;
            case CELL_CROSS:
                mark = CELL_NOUGHT;
                break;
            default:
                // there doesn't really seem to be a concept of panics in C
                // or a way to mark a code path as unreachable so let's do something similar
                puts("panic: invalid cell variant");
                return 1;
        };
    }

    exit:
    free_grid(&grid);

    return 0;
}
