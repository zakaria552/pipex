#include "pipe.h"

void pipe_error(char *msg, int current_pipe[2], int next_pipe[2])
{
	if (current_pipe)
		close_pipe(current_pipe);
	if (next_pipe)
		close_pipe(next_pipe);
	perror("Pipex: %s");
}

void exit_err(char *msg, t_list **cmd_list, int err_code)
{
	errno = err_code;
	if (cmd_list)
		ft_lstclear(cmd_list, (void *) free_cmd);
	perror(msg);
	exit(errno);
}