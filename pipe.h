#ifndef PIPE_H
#define PIPE_H

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "./libft/libft.h"

typedef enum s_cmd_type
{
    INFILE,
    HERE_DOC,
    OUTFILE,
    CMD,
} e_command_type;

typedef struct s_cmd
{
    char *path_name;
    char **cmd;
    e_command_type type;
} t_cmd;


// processor
t_list *process(int argc, char **args);
void free_cmd(t_cmd *cmd);

// pipe
void pipex(int num_cmd, t_list *args);

// pipe utils
void close_pipe(int pipe[2]);
void print_here_doc_input_msg(int num_pipes);

// helpers
void print_cmd_list(t_list *head);
void print_cmd(t_cmd *cmds);
void list_open_fds(char *from, int index);

// io_utils
ssize_t read_write_file(int fd, int write_fd);
void dump_to_outfile(t_cmd *cmd, int pipe[2]);

// execute
void execute(t_cmd *command, int pipe[2], int next_pipe[2], int i);

#endif