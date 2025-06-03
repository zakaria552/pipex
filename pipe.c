#include "pipe.h"
static void close_all_prev_pipes(int pipes[][2], int index);
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
void pipex(int argc, char **argv)
{
    int i;
    int pipes[argc - 2][2];
    char *buff;
    i = -1;

    pipe(pipes[0]);
    dup2(STDIN_FILENO, pipes[0][0]);
    while (++i < argc - 3)
        pipe(pipes[i+1]);
    pipes_fd(pipes, argc - 2);
    i = 0;
    while (i < argc - 3)
    {    
        printf("index: %d\n", i);
        if (fork() == 0)
        {
            printf("Spawning child-%d pid-[%d] cmd-%s\n", i, getpid(), argv[i]);
            close_all_prev_pipes(pipes, i);
            printf("current-pipe-fds: [%d][%d]\n", pipes[i][0], pipes[i][1]);
            close(pipes[i][1]);
            buff = get_next_line(pipes[i][0]);
            close(pipes[i][0]);
            if (!buff)
            {
                printf("Could not read from the pipe %d\n", i);
                exit(-1);
            }
            printf("Content: %s\n", buff);
            printf("next-pipe-fds: [%d][%d]\n", pipes[i+1][0], pipes[i+1][1]);
            close(pipes[i + 1][0]);
            if (write(pipes[i + 1][1], "waffle", 7) < 0)
            {
                printf("Failed to write to the pipe %d\n", i+1);
                close(pipes[i + 1][1]);
                exit(-1);
            }
            printf("Written to pipe-%d\n", i+1);
            printf("-------------------------\n");
            close(pipes[i + 1][1]);
            exit(1);
        }
        i++;
    }
    printf("waiting for last read I: %d\n", i);
    close_all_prev_pipes(pipes, i+1);
    // close(pipes[i][1]);
    // buff =  get_next_line(pipes[i][0]);
    // printf("Last pipe: %s", buff);
    // close(pipes[i][0]);
    // close(pipes[2][0]);


}

void close_all_prev_pipes(int pipes[][2], int index)
{
    index--;
    while (index >= 0)
    {
        printf("Closing pipe-%d\n", index);
        close(pipes[index][0]);
        close(pipes[index][0]);
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