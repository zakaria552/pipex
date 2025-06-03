#ifndef PIPE_H
#define PIPE_H

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "./libft/libft.h"
#include <fcntl.h>

typedef struct s_cmd
{
    char *name;
    char *flags;
} t_cmd;

int read_stdin(char **buff);
int read_write_fd(int read_fd, int write_fd);

#endif