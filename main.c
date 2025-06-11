#include "pipe.h"

void wait_for_child_processes(int *pids, int num_process, int *status)
{
    int i;
    i = -1;
    while (++i < num_process)
    {
        ft_printf("%d: , id: %d\n", i, pids[i]);
        waitpid(pids[i], status, 0);
    }
}

int main(int argc, char **argv)
{
    t_list *args_list;
    int num_cmd;
    int *pids;
    int status;

    args_list = process(argc, argv);
    num_cmd = ft_lstsize(args_list);
	if (num_cmd < 4)
        exit_err("Pipex: must have atleast 4 arguments, (here_doc LIMITTER is treated as one argument)", &args_list, EINVAL);
    if (!args_list)
        exit_err("Pipex: Failed to process args", NULL, errno);
    pids = ft_calloc(num_cmd - 1, sizeof(int));
    if (!pids)
        exit_err("Pipex: Failed to allocate resource", &args_list, errno);
    pipex(num_cmd, &args_list, pids);
    print_cmd_list(args_list);
    ft_lstclear(&args_list, (void *)free_cmd);
    wait_for_child_processes(pids, num_cmd - 2, &status);
    free(pids);
    return WEXITSTATUS(status);
}
