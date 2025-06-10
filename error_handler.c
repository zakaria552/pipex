#include "pipe.h"

void pipe_error(char *msg, int current_pipe[2], int next_pipe[2])
{
	if (current_pipe)
		close_pipe(current_pipe);
	if (next_pipe)
		close_pipe(next_pipe);
	ft_printf("Pipex: %s", msg, strerror(errno));
}