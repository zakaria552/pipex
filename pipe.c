#include "pipe.h"

void list_open_fds(char *from, int index) {
    int max_fd = sysconf(_SC_OPEN_MAX);

    printf("Open file descriptors:\n");
    for (int fd = 0; fd < max_fd; fd++) {
        if (fcntl(fd, F_GETFD) != -1) {
            printf("[%s-%d] FD %d is open\n", from, index, fd);
        }
    }
}

bool map_infile_to_pipe(t_list **args, int pipe_read_end)
{
    t_cmd *cmd;
    t_list *tmp;
    int fd;
    
    list_open_fds("Parent", 0);
    cmd = (*args)->content;
    fd = open(cmd->path_name, O_RDONLY);
    if (fd < 0)
        return false;
    dup2(fd, pipe_read_end);
    close(fd);
    if (fd < 0)
        return false;
    tmp = *args;
    *args = (*args)->next;
    list_open_fds("Parent", 0);
    return true;
}

void close_pipe(int pipe[2])
{
    // printf("Closing pipe[%d][%d]", pipe[0], pipe[1]);
    close(pipe[0]);
    close(pipe[1]);
}

void pipex(int argc, t_list *args)
{
    int pipes[argc - 2][2];
    int i;

    if (pipe(pipes[0]) < 0 || !map_infile_to_pipe(&args, pipes[0][0]))
        return;
    print_cmd_list(args);
    i = 0;
    while(args && args->next != NULL)
    {
        ft_printf("[Parent] - iteration-%d\n", i);
        pipe(pipes[i+1]);
        list_open_fds("iteration", i);
        if (fork() == 0)
        {
            ft_printf("[child-%d] Executing command\n", i);
            // list_open_fds("Child", i);
            execute(args->content, pipes[i], pipes[i+1], i);
        }
        // wait(NULL);
        close_pipe(pipes[i]);
        // exit(1);
        args = args->next;
        i++;
    }
    close(pipes[i][1]);
    read_write_file(pipes[i][0], 1);
    wait(NULL);
    close_pipe(pipes[i]);
}
