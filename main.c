#include "pipe.h"

void wait_for_child_processes(int *pids, int num_process, int *status)
{
    int i;

    i = -1;
    while (++i < num_process)
        waitpid(pids[i], status, 0);
}

int main(int argc, char **argv, char **envp)
{
    t_list *args_list;
    int num_cmd;
    int pids[argc - 3];
    int status;

    args_list = process(argc, argv);
    if (!args_list)
    {
        perror("Failed to process args");
        exit(-1);
    }
    num_cmd = ft_lstsize(args_list);
	if (num_cmd < 4)
    {
        perror("Must have atleast 4 arguments, (here_doc LIMITTER is treated as one argument)");
        ft_lstclear(&args_list, (void *)free_cmd);
        exit(1);
    }
    pipex(num_cmd, args_list, pids);
    ft_lstclear(&args_list, (void *)free_cmd);
    wait_for_child_processes(pids, argc - 3, &status);
    return WEXITSTATUS(status);
}
