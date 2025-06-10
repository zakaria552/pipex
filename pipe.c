#include "pipe.h"

void list_open_fds(char *from, int index) {
    int max_fd = sysconf(_SC_OPEN_MAX);

    printf("Open file descriptors:\n");
    for (int fd = 0; fd < max_fd; fd++) {
        if (fcntl(fd, F_GETFD) != -1) {
            printf("[%s-%d] FD %d is open\n", from, index, fd);
        }
    }
}

void print_doc_input_msg(int num_pipes)
{
    int i;

    i = -1;
    while (++i < num_pipes)
        ft_printf("pipe ");
    ft_printf("heredoc> ");
}

bool map_stdin_to_pipe(char *limiter, int pipe[0], int num_pipes)
{
    char *line;
    
    while (true)
    {
        print_doc_input_msg(num_pipes);
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

void close_pipe(int pipe[2])
{
    close(pipe[0]);
    close(pipe[1]);
}

void dump_to_outfile(t_cmd *cmd, int pipe[2])
{
    int fd;

    if (unlink(cmd->path_name) < 0 && errno != ENOENT)
    {
       ft_printf("Failed to unlink file %s: %s ", cmd->path_name, errno);
       close_pipe(pipe);
       return;
    }
    fd = open(cmd->path_name, O_CREAT | O_WRONLY, 0644);
    if (fd < 0)
    {
        close_pipe(pipe);
        ft_printf("Failed to open file %s: %s", cmd->path_name, strerror(errno));
        return ;
    }
    close(pipe[1]);
    if (read_write_file(pipe[0], fd) < 0)
        ft_printf("Error: %s", strerror(errno));
    close(fd);
    close(pipe[0]);
}

void pipex(int num_cmd, t_list *args)
{
    int pipes[num_cmd - 1][2];
    int i;

    if (pipe(pipes[0]) < 0 || !map_infile_to_pipe(&args, pipes[0]))
        return;
    i = 0;
    while(args && args->next != NULL)
    {
        pipe(pipes[i+1]);
        if (fork() == 0)
            execute(args->content, pipes[i], pipes[i+1], i);
        close_pipe(pipes[i]);
        args = args->next;
        i++;
    }

    dump_to_outfile(args->content, pipes[i]);
}
