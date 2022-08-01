/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_utl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 00:27:30 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/08 12:24:17 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_expand_node(t_ms *mini, t_token *node)
{
	int		i;
	char	*clean;

	i = 0;
	if (ft_strlen_max(node->token, 1) == 0 || node->type == CMD_LITERAL)
		return (SUCCESS);
	node->stored = ft_strdup(node->token);
	ft_do_expand(mini, node);
	if (ft_strcmp(node->stored, node->token) != 0)
		node->tkn_from = FROM_EXPAND;
	clean = ft_remove_lit(node->token, '\\');
	if (clean != NULL)
	{
		ft_safe_free_char(&node->token);
		node->token = clean;
	}
	if (ft_strlen_max(node->token, 1) == 0)
		node->null_tkn = NULL_FROM_EXPAND;
	if (node->tkn_from == FROM_PARSE)
		ft_bichito(mini, node);
	if (node->tkn_from == FROM_PARSE
		&& ft_strcmp(node->stored, node->token) != 0)
		node->tkn_from = FROM_SPC;
	return (SUCCESS);
}

static inline void	ft_fix_args(t_token *token)
{
	t_token	*arg;

	if (token->type == CMD_EXPORT)
		return ;
	arg = token->args;
	while (arg)
	{
		arg->special_tkn = 0;
		arg = arg->next;
	}
}

void	ft_prepare_node(t_ms *mini, t_token *token)
{
	if (!token)
		return ;
	if (!token->args)
		return ;
	ft_fix_args(token);
	ft_solve_wildcards(mini, token, token->args);
}
