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
    OUTFILE,
    CMD,
} e_command_type;

typedef struct s_cmd
{
    char *name;
    char *cmd;
    e_command_type type;
} t_cmd;



int read_stdin(char **buff);
int read_write_fd(int read_fd, int write_fd);
t_list *process(int argc, char **args);

void pipex(int argc, t_list *args);

// helpers
void print_cmd_list(t_list *head);

#endif