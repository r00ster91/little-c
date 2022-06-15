// just some experiments

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct hello {
    char *greetee;
    bool comma;
};

char *create_hello(struct hello h) {
    int i, j, c;
    char world[] = "world";
    char *result =
        malloc(
            (strlen(h.greetee) + h.comma + sizeof(world) - 1)
            * sizeof(char)
        );

    for (i = 0; (c = h.greetee[i]) != 0; ++i)
        result[i] = c;
    if (h.comma)
        result[i++] = ',';
    result[i++] = ' ';
    for (j = 0; (c = world[j]) != 0; ++j)
        result[i + j] = world[j];
    i += sizeof(world) - 1;
    result[i] = 0;
    return result;
}

char *create_hello2(char *greetee) {
    char *s = malloc(strlen("hello, ") + strlen(greetee));
    strcpy(s, "hello, ");
    strcat(s, greetee);
    return s;
}

char *create_hello_struct_keyword(struct hello h) {
    return 0;
}

typedef struct hello hello;

char *create_hello_no_struct_keyword(hello h) {
    return 0;
}

int main() {
    _Bool x = -10;
    ++x;
    printf("%d\n", x);

    char *greetee = "hello world";

    struct hello h = {
        .greetee = greetee,
        .comma = true
    };

    printf("%s\n", create_hello(h));
    printf("%s\n", create_hello2("2d2du092d2u2d90u dw dwdk ookp"));

    return 0;
}
