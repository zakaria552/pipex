#include "pipe.h"

void execute(t_cmd *command, int pipes[][2], t_list **args, int *pids)
{
    char *envp[] = { "PATH=/bin/", NULL};
    int *current_pipe;
    int *next_pipe;

    current_pipe = pipes[0];
    next_pipe = pipes[1];
    if (dup2(current_pipe[0], STDIN_FILENO) < 0 || dup2(next_pipe[1], STDOUT_FILENO) < 0)
    {
        free(pids);
        exit_err("Pipex: ", args, errno);
    }
    close_pipe(current_pipe);
    close_pipe(next_pipe);
    execve(command->path_name, command->cmd, envp);
    ft_lstclear(args, (void *)free_cmd);
    free(pids);
    exit(errno);
}
