#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = open("b.txt", O_RDONLY);
    char *val;
    int num_line = 0;

    if (!fd)
        return 1;
    while ((val = get_next_line(fd)))
    {
        printf("%i: %s\n", num_line, val);
        num_line++;
        free(val);
    }
    close(fd);
    return 0;
}