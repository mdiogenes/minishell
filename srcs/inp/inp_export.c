/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:42:06 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/27 09:49:46 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_arrange_nodes(t_token **args)
{
	t_token	*node;
	t_token	*tmp;

	node = *args;
	while (node)
	{
		if (node->next && node->meta == MTA_TO_EXPORT)
		{
			if (node->next && node->next->meta == MTA_ASSIGN)
			{
				tmp = node->next;
				node->args = tmp;
				if (tmp->next && tmp->next->next)
				{
					node->next = tmp->next->next;
					tmp->next->next = NULL;
				}
				else
					node->next = NULL;
			}
		}
		node = node->next;
	}
}

void	ft_check_export_args(t_token **args, int scn)
{
	t_token	*node;

	node = *args;
	while (node)
	{
		if (scn == 0 && (node->next && node->next->meta == MTA_ASSIGN))
			node->meta = MTA_TO_EXPORT;
		if (scn == 1)
			node->meta = MTA_TO_EXPORT;
		node = node->next;
	}
}

t_token	*ft_args_export_err(t_token *args)
{
	t_token	*tmp;

	if (!args)
		return (NULL);
	tmp = args->next;
	ft_error_export(args);
	if (args->type == CMD_ASSIGN_LE || args->type == CMD_ASSIGN_BE)
	{
		if (tmp)
		{
			free (tmp->token);
			tmp->token = ft_strdup("");
		}
	}
	if (args->type == CMD_ASSIGN_RE)
	{
		ft_delete_node(tmp);
		tmp = NULL;
	}
	ft_delete_node(args);
	return (tmp);
}

void	ft_clean_args_export(t_token **args)
{
	t_token	*node;

	node = *args;
	while (node)
	{
		if (node->meta == MTA_TO_EXPORT)
		{
			if (node->args && node->args->meta == MTA_ASSIGN)
				node->args = ft_args_export_err(node->args);
		}
		node = node->next;
	}
}

int	ft_check_input_export(t_ms *mini)
{
	t_token	*node;

	node = mini->first_token;
	while (node)
	{
		if (node->type == CMD_EXPORT)
		{
			ft_check_export_args(&node->args, 0);
			ft_arrange_nodes(&node->args);
			ft_check_export_args(&node->args, 1);
			ft_clean_args_export(&node->args);
		}
		node = node->next;
	}
	return (SUCCESS);
}
