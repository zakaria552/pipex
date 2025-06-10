#include "pipe.h"

void execute(t_cmd *command, int pipe[2], int next_pipe[2], int i)
{
    char *envp[] = { "PATH=/bin/", NULL};
    
    dup2(pipe[0], STDIN_FILENO);
    dup2(next_pipe[1], STDOUT_FILENO);
    close_pipe(pipe);
    close_pipe(next_pipe);
    execve(command->path_name, command->cmd, envp);
    exit(1);
}