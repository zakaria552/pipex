#include "pipe.h"

void execute(t_cmd *command, int pipe[2], int next_pipe[2], int i)
{
    char *envp[] = { "PATH=/bin", NULL};
    
    print_cmd(command);
    ft_printf("Current pipe-fds[%d][%d] --- next-[%d][%d]\n", pipe[0], pipe[1], next_pipe[0], next_pipe[1]);
    dup2(pipe[0], STDIN_FILENO);
    dup2(next_pipe[1], STDOUT_FILENO);
    close_pipe(pipe);
    close_pipe(next_pipe);
    execve(command->path_name, command->cmd, envp);
    perror("\nErrored");
    ft_printf("Failed to execute-->[cmd: %s]", *command->cmd);
    exit(1);
}