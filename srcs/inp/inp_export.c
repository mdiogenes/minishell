/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:42:06 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/23 11:38:50 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	ft_check_export_args(t_token **args)
{
	t_token	*node;
	int		prev;

	node = *args;
	prev = MTA_TO_EXPORT;
	while (node)
	{
		if (node->meta == MTA_ASSIGN || node->meta == MTA_ASSIGN_EMPTY)
		{
			prev = node->meta;
			node = node->next;
			continue ;
		}
		else if (prev == MTA_ASSIGN_EMPTY)
			node->meta = MTA_TO_EXPORT;
		else if (node->next && node->next->meta == MTA_ASSIGN)
			node->meta = MTA_TO_EXPORT;
		else if (node->next && node->next->meta != MTA_ASSIGN
			&& (prev != MTA_ASSIGN))
			node->meta = MTA_TO_EXPORT;
		prev = node->meta;
		node = node->next;
	}
}

static inline void	ft_args_export_err(t_token *node, t_ms *mini)
{
	if (!node || !node->args)
		return ;
	//ft_error_export(node->args, mini);
	if (node->args->type == CMD_ASSIGN_RE)
	{
		ft_delete_args(node->args);
		node->args = ft_inp_new(ft_strdup("\"\""), mini);
	}
	else
	{
		ft_delete_args(node->args);
		node->args = NULL;
	}
}

static inline int	ft_clean_args_export(t_token **args, t_ms *mini)
{
	t_token	*node;
	t_token	*prev;

	node = *args;
	prev = NULL;
	while (node)
	{
		if (node->args)
		{
			if (node->args->type == CMD_ASSIGN)
				ft_remove_node(node->args, NULL, &node->args);
			else
				ft_args_export_err(node, mini);
		}
		prev = node;
		node = node->next;
	}
	return (SUCCESS);
}

static void	ft_arrange_nodes(t_token **args)
{
	t_token	*node;
	t_token	*end;

	node = *args;
	while (node)
	{
		if (node->meta == MTA_TO_EXPORT
			&& (node->next && node->next->meta != MTA_TO_EXPORT))
		{
			node->args = node->next;
			end = node->next;
			node->next = NULL;
			while (end)
			{
				if (end->next && end->next->meta == MTA_TO_EXPORT)
					break ;
				end = end->next;
			}
			if (end != NULL)
				node->next = end->next;
			if (end != NULL)
				end->next = NULL;
		}
		node = node->next;
	}
}

int	ft_check_input_export(t_ms *mini)
{
	t_token	*node;
	t_token	*prev;

	node = mini->first_token;
	prev = NULL;
	while (node)
	{
		if (node->type == CMD_EXPORT)
		{
			ft_check_export_args(&node->args);
			ft_print_tree_debug("check export; despues export args",mini->first_token);
			ft_arrange_nodes(&node->args);
			if(node->args && node->args->meta != MTA_TO_EXPORT)
			{
				node = ft_remove_node(node, prev, &mini->first_token);
				continue ;
			}
			ft_print_tree_debug("check export; despues arrange args", mini->first_token);
			ft_clean_args_export(&node->args, mini);
			ft_print_tree_debug("check export; despues clean", mini->first_token);
		}
		prev = node;
		node = node->next;
	}
	return (SUCCESS);
}
