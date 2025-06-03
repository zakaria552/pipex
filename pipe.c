#include "pipe.h"
static void close_all_prev_pipes(int *pipes[][2], int index, char *from);
void pipes_fd(int pipes[][2], int num_pipes)
{
    int i;

    i = 0;
    while (i < num_pipes)
    {
        printf("pipe-%d[%d]====[%d]\n", i, pipes[i][0], pipes[i][1]);
        i++;
    }
}
void list_open_fds(char *from, int index) {
    int max_fd = sysconf(_SC_OPEN_MAX);

    printf("Open file descriptors:\n");
    for (int fd = 0; fd < max_fd; fd++) {
        if (fcntl(fd, F_GETFD) != -1) {
            printf("[%s-%d] FD %d is open\n", from, index, fd);
        }
    }
}
void pipex(int argc, char **argv)
{
    int i;
    int pipes[argc - 2][2];
    char *buff;
    i = -1;
    char *child = "Child";
    char *parent = "Parent";

    pipe(pipes[0]);
    dup2(STDIN_FILENO, pipes[0][0]);
    // pipes_fd(pipes, argc - 2);
    i = 0;
    while (i < argc - 3)
    {    
        printf("Iteration: %d\n", i);
        // list_open_fds(parent, 0);
        pipe(pipes[i+1]);
        if (fork() == 0)
        {
            printf("[%s-%d] Spawning pid-[%d] cmd-%s\n", child, i, getpid(), argv[i]);
            // close_all_prev_pipes(pipes, i, child);
            printf("[%s-%d] pipe-[%d] fds: [%d][%d]\n", child, i, i, pipes[i][0], pipes[i][1]);
            // list_open_fds(child, i);
            close(pipes[i][1]);
            buff = get_next_line(pipes[i][0]);
            close(pipes[i][0]);
            if (!buff)
            {
                printf("Could not read from the pipe %d\n", i);
                exit(-1);
            }
            printf("[%s-%d] Content: %s\n", child, i, buff);
            printf("[%s-%d] next-pipe: pipe-%d fds: [%d][%d]\n", child, i, i+1, pipes[i+1][0], pipes[i+1][1]);
            close(pipes[i + 1][0]);
            list_open_fds(child, i);
            if (write(pipes[i + 1][1], "waffle", 7) < 0)
            {
                printf("[%s-%d] Failed to write to the pipe %d\n",child, i, i+1);
                close(pipes[i + 1][1]);
                exit(-1);
            }
            printf("[%s-%d] Written to pipe-%d\n", child, i, i+1);
            printf("-------------------------\n");
            close(pipes[i + 1][1]);
            exit(EXIT_SUCCESS);
        } else {
            close(pipes[i][0]);
            close(pipes[i][1]);
            i++;
        }
    }
    // wait(NULL);
    printf("[%s] waiting for last read I: %d\n", parent, i);
    // close_all_prev_pipes(pipes, i+1, parent);
    // close(pipes[i][1]);
    // close(pipes[i][0]);
    close(pipes[i][1]);
    buff =  get_next_line(pipes[i][0]);
    close(pipes[i][0]);
    printf("Last pipe: %s", buff);
    list_open_fds(parent, 0);


}

void close_all_prev_pipes(int *pipes[][2], int index, char *from)
{
    int i;

    i = index;
    index--;
    while (index >= 0)
    {
        if (*from == 'C')
            printf("[%s-%d] Closing pipe-%d\n", from, i, index);
        else
            printf("[%s] Closing pipe-%d\n", from, index);
        close(*pipes[index][0]);
        close(*pipes[index][0]);
        index--;
    }
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


// #include "pipe.h"
// void pipex(int argc, char **argv)
// {
//     int i;
//     int pipes[argc - 2][2];
//     char *buff;
//     i = -1;

//     pipe(pipes[0]);

//     while (++i < argc - 3)
//         pipe(pipes[i+1]);
//     i = 0;
//     while (i < argc - 3)
//     {    
//         printf("index: %d\n", i);
//         printf("parent-next-pipe-fds: [%d][%d]\n", pipes[i+1][0], pipes[i+1][1]);
//         if (fork() == 0)
//         {
//             printf("argv-[%d][%d]: %s\n", i, getpid(), argv[i]);
//             printf("current-pipe-fds: [%d][%d]\n", pipes[i][0], pipes[i][1]);
//             if (i == 0)
//                 buff = get_next_line(STDIN_FILENO);
//             else {
//                 close(pipes[i][1]);
//                 buff = get_next_line(pipes[i][0]);
//                 close(pipes[i][0]);
//             }

//             if (!buff)
//             {
//                 printf("Could not read from the pipe %d\n", i);
//                 exit(-1);
//             }
//             printf("Content: %s\n", buff);
//             printf("next-pipe-fds: [%d][%d]\n", pipes[i+1][0], pipes[i+1][1]);
//             close(pipes[i + 1][0]);
//             if (write(pipes[i + 1][1], "waffle", 7) < 0)
//             {
//                 printf("Failed to write to the pipe %d\n", i+1);
//                 exit(-1);
//             }
//             printf("Written to pipe\n");
//             printf("-------------------------\n");
//             close(pipes[i + 1][1]);
//             exit(1);
//             break;
//         }
//         i++;
//     }
//     // printf("waiting for last read I: %d\n", i);
//     // close(pipes[0][1]);
//     // close(pipes[0][0]);

//     // close(pipes[1][1]);
//     // close(pipes[1][0]);
//     // wait(NULL);
//     // printf("Last pipe: %s", get_next_line(pipes[i][0]));
//     // close(pipes[2][1]);
//     // close(pipes[2][0]);


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