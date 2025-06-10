#include "pipe.h"
void free_cmd(t_cmd *cmd)
{
	int i;
    char **cmd_flags;
    
    cmd_flags = cmd->cmd;
	i = 0;
	while(cmd_flags && cmd_flags[i])
    {
		free(cmd_flags[i]);
        i++;
    }
    free(cmd_flags);
	free(cmd->path_name);
    free(cmd);
}
int main(int argc, char **argv)
{
    t_list *args_list;
    int num_cmd;

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
        ft_lstclear(&args_list, free_cmd);
        exit(1);
    }
    pipex(num_cmd, args_list);
    ft_lstclear(&args_list, free_cmd);
    return 0;
}
