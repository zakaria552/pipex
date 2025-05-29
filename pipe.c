#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd_in;
    if (argc < 5)
    {
        perror("Must have atleast 4 arguments");
    }
    fd_in = open(argv[1]);
    dup2(fd_in, STDIN_FILENO);
    return 1;
}