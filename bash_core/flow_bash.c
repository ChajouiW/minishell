/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_bash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:51:05 by abahja            #+#    #+#             */
/*   Updated: 2025/05/16 18:27:46 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_redir(t_token *token)
{
	return (token->type == RED_IN || token->type == RED_OUT
		|| token->type == HEREDOC || token->type == APPEND);
}

t_eflow	*ft_last(t_eflow *last)
{
	while (last->next)
		last = last->next;
	return (last);
}

int	quotes(char *s)
{
	if (!s || !*s)
		return (1);
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			if (!ft_strchr(s + 1, *s))
			{
				ft_putstr_fd("error syntax\n", 2);
				return (0);
			}
			else
				s = ft_strchr(s + 1, *s);
		}
		s++;
	}
	return (1);
}

void	the_core(t_minishell *bash)
{
	core_tokinizer(bash);
	expandator(bash, 0);
	ft_spacer(bash);
	if (!bash->token)
		return ;
	if (!syntax(bash))
	{
		exit_status(2);
		return ;
	}
	make_flow(bash, 0, 0, 0);
	if (!here_doc(bash))
		minishell(bash);
	heap_manager(0, 'f', 0);
	state()->is_excution = 0;
	return ;
}
