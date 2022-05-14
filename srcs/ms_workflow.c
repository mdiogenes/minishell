/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_workflow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:33:06 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/14 01:18:16 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_workflow_params(t_token *node)
{
	t_token	*args;
	
	if (node->next->meta > MTA_ARGS)
		return ;
	args = node->next;
	while (args)
	{
		if (args->next && args->next->meta > MTA_ARGS)
			break;
		args = args->next;
	}
	if (args)
	{
		node->next = args->next;
		args->next = NULL;
	}
	else
		node->next = NULL;
}

void	ft_workflow_redir(t_ms *mini)
{
	t_token	*node;
	t_token *tmp;
	char	in;

	in = TKN_STDIN;
	node = mini->first_token;
	while (node)
	{
		if (node->in != in)
			node->in = in;
		if (node->next && node->next->type == RDR_PIPE)
		{
			tmp = node->next;
			node->next = node->next->next;
			ft_delete_node(tmp);
			node->out = TKN_PIPEOUT;
			in = TKN_PIPEIN;
		}
		else
			in = TKN_STDIN;
		node = node->next;
	}
}

void	ft_workflow(t_ms *mini)
{
	t_token	*node;

	node = mini->first_token;
	if (!node || node->meta <= MTA_ARGS)
		return ;
	while (node)
	{
		if (node->next && node->next->meta <= MTA_ARGS)
		{
			node->args = node->next;
			ft_workflow_params(node);
		}
		node = node->next;
	}
	ft_workflow_redir(mini);
}
