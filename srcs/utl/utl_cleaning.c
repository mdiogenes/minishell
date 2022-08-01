/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_cleaning.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:27:39 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/20 17:39:53 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_delete_node(t_token *node)
{
	if (!node)
		return (SUCCESS);
	ft_safe_free_char(&node->token);
	ft_safe_free_char(&node->stored);
	node->token = NULL;
	node->stored = NULL;
	node->next = NULL;
	node->prev = NULL;
	node->args = NULL;
	free (node);
	return (SUCCESS);
}

int	ft_process_branch(t_ms *mini)
{
	t_token	*node;

	if (!mini->first_token)
		return (SUCCESS);
	node = mini->first_token;
	ft_delete_args(node->args);
	mini->first_token = node->next;
	if (mini->last_token == node)
		mini->last_token = NULL;
	ft_delete_node(node);
	return (SUCCESS);
}

t_token	*ft_remove_node(t_token *node, t_token *prev, t_token **head)
{
	t_token	*rst;

	if (!node)
		return (NULL);
	if (prev == NULL)
		*head = node->next;
	else
		prev->next = node->next;
	rst = node->next;
	if (rst)
		rst->prev = prev;
	ft_delete_args(node->args);
	ft_delete_node(node);
	return (rst);
}

void	ft_clear_nodes(t_token **head, t_token **tail)
{
	t_token	*node;

	if (head == NULL || *head == NULL)
		return ;
	while (*head)
	{
		node = *head;
		*head = node->next;
		if (node->args)
			ft_delete_args(node->args);
		ft_delete_node(node);
	}
		*head = NULL;
	if (tail)
		*tail = NULL;
}

void	ft_free_pipes(t_ms *mini)
{
	int	i;

	i = 0;
	if (mini->pipes != NULL)
	{
		while (mini->pipes[i] != NULL)
		{
			if (mini->pipes[i] != NULL)
				free(mini->pipes[i]);
			mini->pipes[i] = NULL;
			i++;
		}
		if (mini->pipes)
			free(mini->pipes);
		mini->pipes = NULL;
	}
}
