/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:25:50 by abahja            #+#    #+#             */
/*   Updated: 2025/05/16 18:30:46 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	execve_fail(char *cmd)
{
	if (errno == EACCES)
	{
		perror(cmd);
		exit_status(126);
	}
	else if (errno == ENOENT)
	{
		perror(cmd);
		exit_status(127);
	}
	else if (errno == ENOEXEC)
	{
		perror(cmd);
		exit_status(1);
	}
	else
	{
		perror(cmd);
		exit_status(1);
	}
}

void	exit_bash(char **arg)
{
	int	i;

	i = 0;
	if (arg_count(arg) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		exit_status(1);
	}
	else if (arg[1])
	{
		if (arg[1][i] == '-' || arg[1][i] == '+')
			i++;
		while (arg[1][i] && ft_isdigit(arg[1][i]))
			i++;
		if (arg[1][i])
		{
			ft_putstr_fd(arg[1], 2);
			ft_putstr_fd(" : exit: numeric argument required\n", 2);
			final_label(exit_status(2));
		}
		else
			final_label(ft_atoi(arg[1]));
	}
	else
		final_label(exit_status(-1));
}
