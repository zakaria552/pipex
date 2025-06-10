#include "pipe.h"

static bool map_infile_to_pipe(t_list **args, int pipe[2]);
static bool map_stdin_to_pipe(char *limiter, int pipe[0], int num_pipes);
static bool map_file_to_pipe(t_cmd *cmd, int pipe[2]);

void pipex(int num_cmd, t_list *args)
{
    int pipes[num_cmd - 1][2];
    int i;

    if (pipe(pipes[0]) < 0 || !map_infile_to_pipe(&args, pipes[0]))
        return;
    i = 0;
    while(args && args->next != NULL)
    {
        if (pipe(pipes[i+1]) < 0)
        {
            close_pipe(pipes[i]);
            return;
        }
        if (fork() == 0)
            execute(args->content, pipes[i], pipes[i+1], i);
        close_pipe(pipes[i]);
        args = args->next;
        i++;
    }

    dump_to_outfile(args->content, pipes[i]);
}


bool map_stdin_to_pipe(char *limiter, int pipe[0], int num_pipes)
{
    char *line;
    
    while (true)
    {
        print_here_doc_input_msg(num_pipes);
        line = get_next_line(STDIN_FILENO);
        if (!line)
            return false;
        if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
            break;
        if (write(pipe[1], line, ft_strlen(line)) < 0)
        {
            free(line);
            return false;
        }
        free(line);
    }
    free(line);
    return true;
}

bool map_file_to_pipe(t_cmd *cmd, int pipe[2])
{
    int fd;
    
    if (access(cmd->path_name,  R_OK) < 0){
        ft_printf("zsh: %s: %s", strerror(errno), cmd->path_name);
        return false;
    }
    fd = open(cmd->path_name, O_RDONLY);
    if (fd < 0)
        return false;
    if (dup2(fd, pipe[0]) < 0)
    {
        close(fd);
        ft_printf("Error: %s", strerror(errno));
        return false;
    }
    close(fd);
    return true;
}

bool map_infile_to_pipe(t_list **args, int pipe[2])
{
    t_cmd *cmd;
    t_list *tmp;
    int fd;
    
    cmd = (*args)->content;
    *args = (*args)->next;
    if (cmd->type == HERE_DOC)
        return map_stdin_to_pipe(cmd->path_name, pipe, ft_lstsize(*args) - 2);
    else 
        return map_file_to_pipe(cmd, pipe);
}
