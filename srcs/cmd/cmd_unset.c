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

t_token	*ft_delete_env(t_token *node, t_token *prev, t_token **mini)
{
	t_token	*rst;

	if (!node)
		return (NULL);
	if (prev == NULL)
		*mini = node->next;
	else
		prev->next = node->next;
	rst = node->next;
	ft_delete_args(node->args);
	ft_delete_node(node);
	return (rst);
}

int	ft_valid_name(char *var, t_ms *mini)
{
	if (!var[0])
		return (0);
	if (ft_isdigit(var[0]))
	{
		mini->exitstatus = 1;
		return (0);
	}
	return (1);
}

int	ft_unset(t_ms *mini)
{
	t_token	*node;
	t_token	*del;
	t_token	*prev;
	char	*var;

	prev = NULL;
	node = mini->first_token->args;
	while (node)
	{
		var = node->token;
		if (!ft_valid_name(var, mini))
			return (ft_error_unset_var(MSG_ERR_NOVALID, node, mini));
		del = ft_find_envar(var, &prev, mini);
		if (!del)
			return (ft_error_unset_var(MSG_ERR_UNSET, node, mini));
		else
			ft_remove_node(del, prev, &mini->env);
		node = node->next;
	}
	ft_process_branch(mini);
	return (SUCCESS);
}
