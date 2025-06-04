// #include "pipe.h"
// static void close_all_prev_pipes(int *pipes[][2], int index, char *from);
// void pipes_fd(int pipes[][2], int num_pipes)
// {
//     int i;

//     i = 0;
//     while (i < num_pipes)
//     {
//         printf("pipe-%d[%d]====[%d]\n", i, pipes[i][0], pipes[i][1]);
//         i++;
//     }
// }

// void pipex(int argc, char **argv)
// {
//     int i;
//     int pipes[argc - 2][2];
//     char *buff;
//     i = -1;
//     char *child = "Child";
//     char *parent = "Parent";

//     pipe(pipes[0]);
//     dup2(STDIN_FILENO, pipes[0][0]);
//     // pipes_fd(pipes, argc - 2);
//     i = 0;
//     while (i < argc - 3)
//     {    
//         printf("Iteration: %d\n", i);
//         // list_open_fds(parent, 0);
//         pipe(pipes[i+1]);
//         if (fork() == 0)
//         {
//             printf("[%s-%d] Spawning pid-[%d] cmd-%s\n", child, i, getpid(), argv[i]);
//             // close_all_prev_pipes(pipes, i, child);
//             printf("[%s-%d] pipe-[%d] fds: [%d][%d]\n", child, i, i, pipes[i][0], pipes[i][1]);
//             // list_open_fds(child, i);
//             close(pipes[i][1]);
//             buff = get_next_line(pipes[i][0]);
//             close(pipes[i][0]);
//             if (!buff)
//             {
//                 printf("Could not read from the pipe %d\n", i);
//                 exit(-1);
//             }
//             printf("[%s-%d] Content: %s\n", child, i, buff);
//             printf("[%s-%d] next-pipe: pipe-%d fds: [%d][%d]\n", child, i, i+1, pipes[i+1][0], pipes[i+1][1]);
//             close(pipes[i + 1][0]);
//             list_open_fds(child, i);
//             if (write(pipes[i + 1][1], "waffle", 7) < 0)
//             {
//                 printf("[%s-%d] Failed to write to the pipe %d\n",child, i, i+1);
//                 close(pipes[i + 1][1]);
//                 exit(-1);
//             }
//             printf("[%s-%d] Written to pipe-%d\n", child, i, i+1);
//             printf("-------------------------\n");
//             close(pipes[i + 1][1]);
//             exit(EXIT_SUCCESS);
//         } else {
//             close(pipes[i][0]);
//             close(pipes[i][1]);
//             i++;
//         }
//     }
//     // wait(NULL);
//     printf("[%s] waiting for last read I: %d\n", parent, i);
//     // close_all_prev_pipes(pipes, i+1, parent);
//     // close(pipes[i][1]);
//     // close(pipes[i][0]);
//     close(pipes[i][1]);
//     buff =  get_next_line(pipes[i][0]);
//     close(pipes[i][0]);
//     printf("Last pipe: %s", buff);
//     list_open_fds(parent, 0);


// }

// void close_all_prev_pipes(int *pipes[][2], int index, char *from)
// {
//     int i;

//     i = index;
//     index--;
//     while (index >= 0)
//     {
//         if (*from == 'C')
//             printf("[%s-%d] Closing pipe-%d\n", from, i, index);
//         else
//             printf("[%s] Closing pipe-%d\n", from, index);
//         close(*pipes[index][0]);
//         close(*pipes[index][0]);
//         index--;
//     }
// }
// int main(int argc, char **argv)
// {
//     int fd_in;
//     if (argc < 5)
//     {
//         perror("Must have atleast 4 arguments");
//         exit(-1);
//     }
//     fd_in = open(argv[1], O_RDONLY);
//     dup2(fd_in, STDIN_FILENO);
//     argv+=2;
//     pipex(argc, argv);
//     return 1;
// }


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
    int fd;
    t_list *tmp;
    
    list_open_fds("Parent", 0);
    cmd = (*args)->content;
    fd = open(cmd->name, O_RDONLY);
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
    printf("Closing pipe[%d][%d]", pipe[0], pipe[1]);
    close(pipe[0]);
    close(pipe[1]);
}

void pipex(int argc, t_list *args)
{
    t_cmd *cmd;
    int pipes[argc - 2][2];
    int i;

    if (pipe(pipes[0]) < 0 || !map_infile_to_pipe(&args, pipes[0][0]))
        return;
    print_cmd_list(args);
    i = 0;
    while(args)
    {
        printf("[Parent] - iteration-%d\n", i);
        pipe(pipes[i+1]);
        // if (pipe(pipes[i+1]) < 0)
        // if (fork() == 0)
        //     //execute_cmd();
        close_pipe(pipes[i]);
        args = args->next;
        i++;
    }
    close_pipe(pipes[i]);
    list_open_fds("Parent", 0);

}
