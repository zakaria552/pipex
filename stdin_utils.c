#include "pipe.h"

int read_stdin(char **buff)
{
    ssize_t bytes_read;
    while (bytes_read = read(stdin, *buff, 1024) > 0)

    if (bytes_read < 0)
        return (-1);
    return 1;
}

int read_write_fd(int read_fd, int write_fd)
{
    ssize_t bytes_read;
    char *buff;

    bytes_read = 0;
    while (true)
    {
        buff = get_next_line(read_fd);
        if (!buff)
            break;
        bytes_read += ft_strlen(buff);
        if (write(write_fd, buff, bytes_read) < 0)
            return -1;
        free(buff);
    }
    if (bytes_read < 0)
        return -1;
    return 1;
}