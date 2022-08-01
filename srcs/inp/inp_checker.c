/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 00:25:23 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/07 10:54:45 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_branch(t_ms *mini)
{
	t_token	*node;

	node = mini->first_token;
	while (node && node->meta < MTA_NEXT)
	{
		if (node->type == IMP_FROM_FILE)
		{
			if (node->next)
				node->next->sp_tkn = SILENCED_CHECK;
		}
		if (node->to_out == 2 && (node->type == RDR_TO_FILE
				|| node->type == RDR_APP_FILE))
			node->sp_tkn = SILENCED_CHECK;
		node = node->next;
	}
	return (SUCCESS);
}

static inline t_token	*ft_clear_inp_err(t_ms *mini, t_token *node,
		t_token *prev)
{
	while (node && node->type == IMP_FROM_FILE)
		node = ft_remove_node(node, prev, &mini->first_token);
	return (node);
}

void	ft_check_imp_file(t_ms *mini)
{
	t_token	*node;
	t_token	*prev;

	node = mini->first_token;
	prev = NULL;
	while (node && node->meta < MTA_NEXT)
	{
		if (node->type == IMP_FROM_FILE
			&& (node->next && node->next->type == IMP_FROM_FILE))
		{
			if (access(node->args->token, F_OK | R_OK) != 0)
			{
				if (node->next && node->next->type == IMP_FROM_FILE)
					node = ft_clear_inp_err(mini, node->next, node);
			}
			else
				node = ft_remove_node(node, prev, &mini->first_token);
			continue ;
		}
		prev = node;
		node = node->next;
	}
}
