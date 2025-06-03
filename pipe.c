#include "pipe.h"
void pipex(int argc, char **argv)
{
    int i;
    int pipes[argc - 3][2];
    int j;
    char *buff;
    i = 0;
    j = 0;

    pipe(pipes[0]);
    close(pipes[0][1]);
    dup2(STDIN_FILENO, pipes[0][0]);

    while (i < argc - 3)
    {
        ft_printf("argv-[%d][%d]: %s\n", i, getpid(), argv[i]);
        if (fork() == 0)
        {
            close(pipes[i][1]);
            buff = get_next_line(pipes[i][0]);
            if (!buff)
            {
                ft_printf("Could not read from the pipe %d\n", i);
                exit(-1);
            }
            ft_printf("Child read from pipe-[%d]: [%s]\n", i, buff);
            ft_printf("fds: [%d][%d]\n", pipes[i][0], pipes[i][1]);
            close(pipes[i][0]);
            pipe(pipes[i+1]);
            ft_printf("fds: [%d][%d]\n", pipes[i+1][0], pipes[i+1][1]);
            close(pipes[i + 1][0]);
            write(pipes[i + 1][1], "waffle", 7);
            // read_write_fd(pipes[i][0], pipes[i + 1][1]);
            close(pipes[i+1][1]);
            break;
        }
        i++;
    }
    close(pipes[0][0]);
}

int main(int argc, char **argv)
{
    int fd_in;
    if (argc < 5)
    {
        perror("Must have atleast 4 arguments");
        exit(-1);
    }
    fd_in = open(argv[1], O_RDONLY);
    dup2(fd_in, STDIN_FILENO);
    argv+=2;
    pipex(argc, argv);
    return 1;
}