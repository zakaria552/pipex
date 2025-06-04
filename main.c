#include "pipe.h"

int main(int argc, char **argv)
{
    t_list *processed_args;
    
	if (argc < 5)
    {
        perror("Must have atleast 4 arguments");
        exit(-1);
    }
    processed_args = process(argc, argv);
    if (!processed_args)
    {
        perror("Failed to process args");
        exit(-1);
    }
    print_cmd_list(processed_args);
    pipex(argc, processed_args);
    
    // dup2(fd_in, STDIN_FILENO);
    // argv+=2;
    // pipex(argc, argv);
    ft_lstclear(&processed_args, free);
    return 0;
}
