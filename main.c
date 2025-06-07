#include "pipe.h"
void free_cmd(t_cmd *cmd)
{
    free(cmd->path_name);
    free(cmd->cmd);
}
int main(int argc, char **argv)
{
    t_list *args_list;
    
	if (argc < 5)
    {
        perror("Must have atleast 4 arguments");
        exit(-1);
    }
    args_list = process(argc, argv);
    if (!args_list)
    {
        perror("Failed to process args");
        exit(-1);
    }
    print_cmd_list(args_list);
    pipex(argc, args_list);
    ft_lstclear(&args_list, free_cmd);
    return 0;
}
