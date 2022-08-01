/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_expand_chars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:45:19 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/05 14:45:22 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	*ft_cdbichito(t_ms *mini)
{
	if (ft_find_envar_export("HOME", mini) == NULL)
		return (mini->homecons);
	else
		return (ft_find_envar_export("HOME", mini)->args->token);
}

int	ft_bichito(t_ms *mini, t_token *node)
{
	char	*temp;
	char	*tkn_one;

	if (node->type == CMD_LITERAL || node->tkn_from == FROM_EXPAND)
		return (0);
	if (node->type != CMD_EXPAND && ft_strncmp(node->token, "~/", 2) == 0)
	{
		tkn_one = ft_strdup(&node->token[1]);
		temp = ft_strdup(ft_cdbichito(mini));
		temp = ft_strjoin_clean(&temp, &tkn_one, 0);
		ft_safe_free_char(&node->token);
		node->token = temp;
		return (1);
	}
	if (node->type != CMD_EXPAND && ft_strict_cmp(node->token, "~") == 0)
	{
		ft_safe_free_char(&node->token);
		node->token = ft_strdup(ft_cdbichito(mini));
		return (1);
	}
	return (0);
}
