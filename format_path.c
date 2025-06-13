/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:49:04 by zfarah            #+#    #+#             */
/*   Updated: 2025/06/13 17:45:16 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static char	*join_cmd_path(char *env_path, char *cmd);
static char	*get_exc_path(char **paths, char *cmd);
static char	*get_env_variable(char **envp, char *variable);

char	*format_path(char *command, char **envp)
{
	char	**paths;
	char	*exc_path;

	if (ft_strchr(command, '/'))
	{
		exc_path = ft_strdup(command);
		if (!exc_path)
			return (set_errno(ENOMEM));
		if (access(exc_path, X_OK) == 0)
			return (exc_path);
		else
		{
			free(exc_path);
			ft_printf("Pipex: %s: %s\n", strerror(errno), command);
			return (set_errno(errno));
		}
	}
	paths = ft_split(get_env_variable(envp, "PATH="), ':');
	if (!paths)
		return (set_errno(ENOMEM));
	exc_path = get_exc_path(paths, command);
	if (!exc_path)
		ft_printf("Pipex: command not found: %s\n", command);
	free_matrix_mem(paths);
	return (exc_path);
}

char	*join_cmd_path(char *env_path, char *cmd)
{
	size_t	len_env_path;
	size_t	len_cmd;
	char	*joint;

	len_cmd = ft_strlen(cmd);
	len_env_path = ft_strlen(env_path);
	joint = malloc(sizeof(char) * (len_env_path + len_cmd + 2));
	if (!joint)
		return (NULL);
	ft_memcpy(joint, env_path, len_env_path);
	ft_memcpy(joint + len_env_path, "/", 1);
	ft_memcpy(joint + len_env_path + 1, cmd, len_cmd);
	joint[len_cmd + len_env_path + 1] = '\0';
	return (joint);
}

char	*get_exc_path(char **paths, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		cmd_path = join_cmd_path(paths[i], cmd);
		if (!cmd_path)
			return (set_errno(ENOMEM));
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	errno = EKEYEXPIRED;
	return (NULL);
}

char	*get_env_variable(char **envp, char *variable)
{
	size_t	len;
	int		i;

	len = ft_strlen(variable);
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], variable, len) == 0)
			return (envp[i] + len);
	}
	return (NULL);
}
