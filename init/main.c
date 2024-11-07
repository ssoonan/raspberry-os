#include "../lib/lib.h"

int main(void)
{
    int fd;

    fd = open_file("TEST.BIN");
    if (fd == -1) {
        printf("open file failed\r\n");
    }
    else {
        int size = get_file_size(fd);
        printf("the size of file is %d open file succeeds\r\n", size);
    }

    close_file(fd);
    
    return 0;
}