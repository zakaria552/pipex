#include "pipe.h"

void execute(t_cmd *command, int pipe[2], int next_pipe[2])
{
    dup2(pipe[0], STDIN_FILENO);
    // dup2(STDOUT_FILENO, next_pipe[1]);
    // close_pipe(pipe);
    print_cmd(command);
    // printf("stdin-->[");
    // printf("]--end");
    // printf("bytes_written: %zu\n", read_write_file(pipe[0], 1));
    // printf("pipe-[%d][%d]\n", pipe[0], pipe[1]);
    execv(command->path_name, command->cmd);
    printf("Failed to execute-->");
    exit(1);
}