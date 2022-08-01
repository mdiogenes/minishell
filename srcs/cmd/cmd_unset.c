/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:30:46 by msoler-e          #+#    #+#             */
/*   Updated: 2022/06/23 11:31:27 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_find_envar(char *needle, t_token **prev, t_ms *mini)
{
	t_token	*node;
	size_t	len;

	node = mini->env;
	while (node)
	{
		len = ft_strlen(node->token);
		if (len == ft_strlen(needle)
			&& ft_strncmp(node->token, needle, len) == 0)
			return (node);
		*prev = node;
		node = node->next;
	}
	return (NULL);
}

t_token	*ft_delete_env(t_token *node, t_token *prev, t_ms *mini)
{
	if (ft_strict_cmp(node->token, "PATH") == 0)
	{
		ft_clear_tabs(mini->bin_paths);
		mini->bin_paths = NULL;
	}
	return (ft_remove_node(node, prev, &mini->env));
}

int	ft_unset(t_ms *mini)
{
	t_token	*node;
	t_token	*del;
	t_token	*prev;

	prev = NULL;
	node = mini->first_token->args;
	while (node)
	{
		if (ft_check_var_name(node->token) == IS_FALSE)
		{
			ft_export_id_error(mini, node);
			node = node->next;
			continue ;
		}
		del = ft_find_envar(node->token, &prev, mini);
		if (del != NULL)
			ft_delete_env(del, prev, mini);
		node = node->next;
	}
	ft_process_branch(mini);
	return (SUCCESS);
}
