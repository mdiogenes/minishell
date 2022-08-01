/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:06:43 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/15 14:06:46 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_select_dir(t_ms *mini)
{
	DIR	*dir;

	dir = opendir(mini->stored);
	if (dir == NULL)
	{
		ft_safe_free_char(&mini->stored);
		mini->stored = ft_strdup(mini->path);
		mini->status_tkn = 0;
		return (ERROR);
	}
	closedir(dir);
	mini->status_tkn = 1;
	return (SUCCESS);
}

static inline void	ft_prepare_to_wild(t_token *node, t_ms *mini)
{
	ft_safe_free_char(&mini->stored);
	ft_safe_free_char(&node->stored);
	node->stored = ft_strdup(node->token);
}

char	*ft_get_bns_path(t_token *node, t_ms *mini)
{
	char	*evl;
	size_t	len;

	ft_prepare_to_wild(node, mini);
	evl = ft_strrchr(node->token, '/');
	len = 0;
	if (evl == NULL)
		return (mini->path);
	else
	{
		while ((node->token + len) != evl)
			len++;
		if (*(evl + 1))
			len++;
		else
			return (mini->path);
		evl++;
		mini->stored = ft_strndup(node->token, len);
		if (ft_select_dir(mini) == ERROR)
			return (mini->path);
		ft_safe_free_char(&node->token);
		node->token = ft_strdup(evl);
		return (mini->stored);
	}
}

int	ft_solve_wildcards(t_ms *mini, t_token *cmd, t_token *node)
{
	if (!node)
		return (IS_FALSE);
	if (!node->args && !node->next)
		return (ft_change_wildcard(mini, cmd, node));
	if (node->args && node->next)
		return (ft_solve_wildcards(mini, cmd, node->args)
			+ ft_solve_wildcards(mini, cmd, node->next)
			+ ft_change_wildcard(mini, cmd, node));
	if (!node->args && node->next)
		return (ft_solve_wildcards(mini, cmd, node->next)
			+ ft_change_wildcard(mini, cmd, node));
	return (ft_solve_wildcards(mini, cmd, node->args)
		+ ft_change_wildcard(mini, cmd, node));
}
