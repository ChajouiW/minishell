/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_polisher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:00:10 by abahja            #+#    #+#             */
/*   Updated: 2025/05/16 18:14:43 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**alloc_arg(t_token *t)
{
	int		i;
	char	**args;
	char	**split;
	int		j;

	i = 0;
	while (t && t->type != PIPE)
	{
		if (!t->visited)
		{
			if (t->ambiguous)
			{
				split = ft_split(t->brick, ' ');
				j = i;
				while (split[i - j])
					i++;
			}
			else
				i++;
		}
		t = t->next;
	}
	args = heap_manager(sizeof(char *) * (i + 1), 'x', NULL);
	args[i] = NULL;
	return (args);
}

void	cmd_setup(t_eflow *flow, t_token *t, int *i, char **args)
{
	int	j;

	if (t->ambiguous)
		args = ft_split(t->brick, ' ');
	if (!*i)
	{
		if (t->ambiguous && args)
			flow->cmd = ft_strdup(args[0]);
		else
			flow->cmd = ft_strdup(t->brick);
		is_builtin(flow);
	}
	if (t->ambiguous)
	{
		j = -1;
		while (args[++j])
			flow->arg[(*i)++] = ft_strdup(args[j]);
	}
	else
		flow->arg[(*i)++] = ft_strdup(t->brick);
}

void	check_cmd(t_eflow *flow, t_token *t)
{
	int		i;

	while (t && t->visited)
		t = t->next;
	flow->arg = alloc_arg(t);
	i = 0;
	while (t && t->type != PIPE)
	{
		if (!t->visited)
		{
			cmd_setup(flow, t, &i, 0);
			t->visited = 1;
		}
		t = t->next;
	}
	if (t)
		t->visited = 2;
}

void	make_flow(t_minishell *bash, t_token *t, t_re *redir, t_type type)
{
	t = bash->token;
	while (t)
	{
		redir = NULL;
		while (t && t->type != PIPE)
		{
			if (is_redir(t))
			{
				type = t->type;
				t = t->next;
				if (t)
				{
					t->visited = 1;
					t->prev->visited = 1;
					re_add_new(&redir, create_re(type, t));
				}
			}
			t = t->next;
		}
		flow_add_new(&bash->flow, create_flow(redir));
		check_cmd(ft_last(bash->flow), bash->token);
		if (t && t->type == PIPE)
			t = t->next;
	}
}
