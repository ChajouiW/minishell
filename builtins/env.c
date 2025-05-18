/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:25:53 by abahja            #+#    #+#             */
/*   Updated: 2025/05/16 18:29:56 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	arg_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	env(char **env, char **arg)
{
	int	i;

	i = 0;
	if (!env || !*env)
		return ;
	if (arg_count(arg) > 1)
	{
		ft_putstr_fd(arg[0], 2);
		ft_putstr_fd(" too many arguments\n", 2);
		exit_status(1);
		return ;
	}
	while (env[i])
	{
		if (env[i][0])
			printf("%s\n", env[i]);
		i++;
	}
	exit_status(0);
}
