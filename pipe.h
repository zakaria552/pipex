/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:33:38 by zfarah            #+#    #+#             */
/*   Updated: 2025/06/12 15:56:33 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum s_cmd_type
{
	INFILE,
	HERE_DOC,
	OUTFILE,
	CMD,
}					t_command_type;

typedef struct s_cmd
{
	char			*path_name;
	char			**cmd;
	char			**envp;
	t_command_type	type;
}					t_cmd;

// processor
t_list				*process(int argc, char **args, char **envp);

// format_path
char	*format_path(char *command, char **envp);

// cmd_utils
void				free_cmd(t_cmd *cmd);
void	*free_matrix_mem(char **matrix);
bool cmds_validated(t_list *cmds);

// pipe
void				pipex(int num_cmd, t_list **cmd_list, int *pids);

// pipe utils
void				close_pipe(int pipe[2]);
void				print_here_doc_input_msg(int num_pipes);

// helpers
void				print_cmd_list(t_list *head);
void				print_cmd(t_cmd *cmds);
void				list_open_fds(char *from, int index);

// io_utils
ssize_t				read_write_file(int fd, int write_fd);
void				dump_to_outfile(t_cmd *cmd, int pipe[2]);

// execute
void				execute(t_cmd *command, int pipes[][2], t_list **args,
						int *pids);

// error handler
void				pipe_error(char *msg, int current_pipe[2],
						int next_pipe[2]);
void				exit_err(char *msg, t_list **cmd_list, int err_code);
void	*set_errno(int err_code);

#endif