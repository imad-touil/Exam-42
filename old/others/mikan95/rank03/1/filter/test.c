#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

int main() {
    int fd = open("non_existent_file.txt", O_RDONLY);
    if (fd == -1) {
        perror("Hello");
    }
    return 0;
}
