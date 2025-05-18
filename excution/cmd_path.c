/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:45:50 by mochajou          #+#    #+#             */
/*   Updated: 2025/05/16 18:36:56 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*the_real_finder(t_eflow *flow, char **path, char *cmd_path, int i)
{
	char	no_acess;

	no_acess = 0;
	while (path[i])
	{
		cmd_path = ft_pathjoin(path[i], flow->cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		if (errno == EACCES)
			no_acess = 1;
		free(cmd_path);
		i++;
	}
	if (no_acess)
	{
		errno = EACCES;
		perror(flow->cmd);
		exit_status(126);
	}
	else
	{
		(ft_putstr_fd(flow->cmd, 2), ft_putstr_fd(": command not found\n", 2));
		exit_status(127);
	}
	return (NULL);
}

static char	*check_everything(char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == -1)
		{
			exit_status(126);
			perror(cmd);
			return (NULL);
		}
		return (cmd);
	}
	exit_status(127);
	perror(cmd);
	return (NULL);
}

static char	*is_dir(char *cmd, char *tmp, char *cmd_path)
{
	struct stat	x;

	stat(cmd, &x);
	if (S_ISDIR(x.st_mode))
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit_status(126);
		return (NULL);
	}
	if (cmd[0] == '.' && cmd[1] == '/')
	{
		tmp = getcwd(NULL, 0);
		cmd_path = ft_strjoin(tmp, cmd + 1);
		free(tmp);
		return (check_everything(cmd_path));
	}
	return (check_everything(cmd));
}

char	*path_finder(t_eflow *flow, char **env)
{
	char	**path;
	char	*cmd_path;
	char	*tmp;

	cmd_path = NULL;
	tmp = NULL;
	if (ft_strchr(flow->cmd, '/'))
		return (is_dir(flow->cmd, tmp, cmd_path));
	path = ft_split(env_path(env), ':');
	if (!path)
	{
		ft_putstr_fd(flow->cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit_status(127);
		return (NULL);
	}
	if (flow->cmd[0] == '\0')
	{
		ft_putstr_fd("Command '' not found\n", 2);
		exit_status(127);
		return (NULL);
	}
	cmd_path = the_real_finder(flow, path, cmd_path, 0);
	return (cmd_path);
}
