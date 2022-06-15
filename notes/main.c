/*
 * This program lets you take notes, mark them as done, and save them to a file.
 */

#include <stdio.h>
#include <stdlib.h>

// who needs `typedef`s or `stdbool.h`?

struct Note {
    // this includes a final newline
    char *content;
    _Bool done;
};

void print_no_notes() {
    printf("No notes have been taken yet.\n");
}

void print_notes(struct Note *notes, size_t notes_len) {
    printf("Notes:\n");
    for (size_t i = 0; i < notes_len; ++i) {
        struct Note note = notes[i];
        printf("%ld. [%c] %s", i + 1, note.done ? 'x' : ' ', note.content);
    }
}

/* lets the user select a note and returns its index */
ssize_t /* don't confuse this with `size_t`! `ssize_t` can additionally be used for an error (a negative value)
         * but `size_t` can't.
         */
select_note(size_t notes_len) {
    printf("Please select a note from 1 to %ld (including %ld): ", notes_len, notes_len);
    unsigned i;
    if (scanf("%u", &i) != 1) return -1;
    if (!(i >= 1 && i <= notes_len)) return -1;
    return i - 1;
}

int a() {
    return 99;
}

int main() {
    int (*fn)(void) = a;
    fn = fn;
    unsigned char *a_bytes = (unsigned char *)a;

    for (int j = 0; j < 10; ++j) {
        if (a_bytes[j] == 99)
            printf("found return value %d in function `a`\n", a_bytes[j]);
    }

    int arr[2] = {1, 2}, x = 3;

    printf("%d, %d\n", x, arr[2]); // if aliasing occurred, this will print `3`!
                                   // It depends on the C compiler implementation (and their codegen) so it shouldn't be relied on that
                                   // `x` comes directly after `arr` in stack memory!
                                   // aliasing here means that `x` and `arr[2]` refer to the same stack memory

    struct Note *notes = 0;
    size_t notes_len = 0, i, len;
    ssize_t bytes_read;
    char *content = 0;
    FILE *file;

    file = fopen("notes", "r");
    if (file == 0) {
        print_no_notes();
    } else {
        // if `content` is 0, it allocates a new buffer
        for (i = 0; (bytes_read = getline(&content, &len, file)) != EOF; ++i) {
            struct Note *new_notes = realloc(notes, sizeof(struct Note) * i);
            new_notes[i] = (struct Note){
                .content = content,
                .done = 0,
            };
            content = 0; // allocate new memory next time
            notes = new_notes;
        }
        notes_len = i;
        printf("Notes:\n");
    }

    for (size_t j = 0; j < 5; ++j);
    // j = j; // this doesn't work, `j` is declared in `for`

    while (1) {
        printf(
            "1. View notes\n"
            "2. Add note\n"
            "3. Mark note as done\n"
            "4. Exit\n"
            "> "
        );

        unsigned input;
        if (scanf("%u", &input) != 1) continue;

        // discard newline
        int newline = getchar();
        if (newline != '\n') continue;

        switch (input) {
            case 1:
                if (!notes)
                    print_no_notes();
                else
                    print_notes(notes, notes_len);
                break;
            case 2:
                bytes_read = getline(&content, &len, stdin);
                if (bytes_read == -1) {
                    puts("failed to read note");
                    return 1;
                }
                struct Note note = {
                    .content = content,
                    .done = 0,
                };
                content = 0;

                i = notes_len;
                ++notes_len;
                struct Note *new_notes = realloc(notes, sizeof(struct Note) * notes_len);
                if (!new_notes) {
                    puts("allocation failed");
                    return 1;
                }
                new_notes[i] = note;
                notes = new_notes;
                puts("Note saved!");
                break;
            case 3:
                if (!notes) {
                    print_no_notes();
                    break;
                }
                print_notes(notes, notes_len);
                ssize_t i = select_note(notes_len);
                if (i >= 0) {
                    size_t i = i;
                    notes[i].done = 1;

                    _Bool all_notes_done = 1;
                    for (i = 0; i < notes_len; ++i) {
                        if (!notes[i].done) {
                            all_notes_done = 0; // short-circuit
                            break;
                        }
                    }
                    if (all_notes_done)
                        puts("All notes completed!");
                    else
                        puts("Note completed!");
                } else {
                    puts("Invalid index!");
                }
                break;
            case 4:
                file = fopen("notes", "w");
                if (!file) {
                    puts("could not open file for writing");
                    return 1;
                }
                for (size_t i = 0; i < notes_len; ++i)
                    fprintf(file, "%d%s", notes[i].done, notes[i].content);
                return 0;
        }
        putchar('\n');
    }

    return 0;
}
