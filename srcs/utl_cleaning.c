/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_cleaning.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 00:15:17 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/01 11:46:15 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_tabs(char **tab)
{
	size_t	i;

	i = -1;
	if (!tab)
		return ;
	free (tab);
}

int	ft_delete_node(t_token *node)
{
	if (!node)
		return (SUCCESS);
	if (node->token)
		free (node->token);
	node->next = NULL;
	node->args = NULL;
	free (node);
	return (SUCCESS);
}

int	ft_delete_args(t_token *node)
{
	if (!node)
		return (SUCCESS);
	if (!node->args && !node->next)
		return (ft_delete_node(node));
	if (node->args && node->next)
		return (ft_delete_args(node->args)
			+ ft_delete_args(node->next)
			+ ft_delete_node(node));
	if (!node->args && node->next)
		return (ft_delete_args(node->next)
			+ ft_delete_node(node));
	return (ft_delete_args(node->args)
		+ ft_delete_node(node));
}

int	ft_process_branch(t_ms *mini)
{
	t_token	*node;

	if (!mini->first_token)
		return (SUCCESS);
	node = mini->first_token;
	ft_delete_args(node->args);
	mini->first_token = node->next;
	ft_delete_node(node);
	return (SUCCESS);
}

void	ft_clear_nodes(t_ms *mini)
{
	t_token	*node;

	if (mini->first_token)
	{
		while (mini->first_token)
		{
			node = mini->first_token->next;
			ft_process_branch(mini);
			mini->first_token = node;
		}
	}
}
