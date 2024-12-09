#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = open("1char.txt", O_RDONLY);
    char *val;
    int num_line = 0;

    val = get_next_line(fd);
    printf("%i: %s", num_line + 1, val);
    free(val);
        val = get_next_line(fd);
    printf("%i: %s", num_line + 1, val);
    free(val);
    free(val);
    close(fd);
    return 0;
}
