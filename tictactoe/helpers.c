#include <stdio.h>

// I think function documentation only goes into the headers
unsigned read_number(unsigned const max, char *error) {
    int number;

    printf("> ");
    // `getline` would work better here but I went with `scanf` for now
    int res = scanf("%d", &number);

    // discard trailing newline
    int newline = getchar();
    (void)(newline);

    if (res != 1 || number <= 0) {
        // we didn't match our only input item
        puts("Invalid input! Please try again.");
        return read_number(max, error); // let's hope this tail call gets optimized out
                                        // so that this would be as fast as a loop and we wouldn't ever get a stack overflow
    } else if ((unsigned)number > max) {
        puts(error);
        return read_number(max, error); // same here
    } else {
        putchar('\n');
        return number;
    }
}
