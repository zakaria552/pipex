#ifndef PIPE_H
#define PIPE_H

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "./libft/libft.h"
#include <fcntl.h>

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



int read_stdin(char **buff);
int read_write_fd(int read_fd, int write_fd);
t_list *process(int argc, char **args);

void pipex(int argc, t_list *args);
void close_pipe(int pipe[2]);
void list_open_fds(char *from, int index);

// helpers
void print_cmd_list(t_list *head);
void print_cmd(t_cmd *cmds);

ssize_t read_write_file(int fd, int write_fd);
void execute(t_cmd *command, int pipe[2], int next_pipe[2], int i);

#endif