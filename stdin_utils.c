#include "pipe.h"

int read_stdin(char **buff)
{
    ssize_t bytes_read;
    while (bytes_read = read(stdin, *buff, 1024) > 0)

    if (bytes_read < 0)
        return (-1);
    return 1;
}

ssize_t read_write_file(int fd, int write_fd)
{
    char buff[BUFFER_SIZE + 1];
    ssize_t written_bytes;
    ssize_t bytes_read;
    
    ft_memset(buff, 0, BUFFER_SIZE);
    bytes_read = read(fd, buff, BUFFER_SIZE);
    written_bytes = bytes_read;
    ft_printf("Reading-%d to %d\n", fd, write_fd);
    while (bytes_read > 0)
    {
        if (write(write_fd, buff, bytes_read) < 0)
            return -1;
        ft_memset(buff, 0, bytes_read);
        bytes_read = read(fd, buff, BUFFER_SIZE);
        written_bytes+= bytes_read;
    }
    if (bytes_read < 0 )
        return -1;
    return (written_bytes);
}

