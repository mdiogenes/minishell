/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 21:14:52 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/25 00:58:18 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	ft_clean_quotes(t_ms *mini)
{
	t_token	*node;
	t_token	*prev;

	node = mini->first_token;
	prev = NULL;
	while (node && node->meta < MTA_NEXT)
	{
		if (node->type == CMD_LITERAL || node->type == CMD_EXPAND)
		{
			if (ft_count_char(node->token, '"') > 0
				|| ft_count_char(node->token, '\'') > 0)
			{
				if (node->type == CMD_LITERAL)
					node->token = ft_strtrim_clean(node->token, "\'");
				else if (node->type == CMD_EXPAND)
					node->token = ft_strtrim_clean(node->token, "\"");
			}
			if (ft_strlen_max(node->token, 1) == 0)
				node->null_tkn = NULL_FROM_PARSE;
		}
		prev = node;
		node = node->next;
	}
}

static inline void	ft_set_node(t_token *node)
{
	if (ft_strlen_max(node->token, 1) == 0)
	{
		if (node->null_tkn == NOT_NULL)
			node->null_tkn = NULL_FROM_PARSE;
	}
	else
		node->null_tkn = NOT_NULL;
	node->type = ft_read_from_node(node->token);
	node->meta = ft_get_meta_type(node->type);
	node->status = FROM_PARSE;
	node->special_tkn = 0;
	node->exp_sts = 0;
}

static inline void	ft_check_to_join(t_ms *mini)
{
	t_token			*node;
	t_token			*next;
	t_token			*prev;

	node = mini->first_token;
	prev = NULL;
	while (node && node->meta < MTA_NEXT)
	{
		next = node->next;
		if (next == NULL)
			break ;
		if (next && next->meta < MTA_REDIR_FILE && node->meta < MTA_REDIR_FILE
			&& (node->sp_tkn % 2) == 0 && node->null_tkn != NULL_FROM_PARSE)
		{
			next->token = ft_strjoin_clean(&node->token, &next->token, 2);
			node = ft_remove_node(node, prev, &mini->first_token);
			ft_set_node(node);
			continue ;
		}
		prev = node;
		node = node->next;
	}
}

static inline void	ft_redir_reset(t_ms *mini)
{
	t_token	*node;
	t_token	*prev;

	node = mini->first_token;
	prev = NULL;
	while (node && node->meta < MTA_NEXT)
	{
		ft_set_node(node);
		node->prev = prev;
		if (ft_strict_cmp(node->token, "2") == 0)
		{
			if (node->next && node->next->type == RDR_TO_FILE)
			{
				node = ft_remove_node(node, prev, &mini->first_token);
				node->to_out = 2;
				continue ;
			}
		}
		prev = node;
		node = node->next;
	}
}

int	ft_syntax_check(t_ms *mini)
{
	t_token	*node;
	t_token	*prev;

	node = mini->first_token;
	prev = NULL;
	ft_clean_quotes(mini);
	ft_get_expand(mini, node, ft_expand_node);
	while (node && node->meta < MTA_NEXT)
	{
		if (node->meta == MTA_REDIR_FILE && node->next
			&& node->next->null_tkn == NULL_FROM_EXPAND)
			return (ft_ambiguous_error(mini, node->next->stored));
		if (node->null_tkn == NULL_FROM_EXPAND)
		{
			node = ft_remove_node(node, prev, &mini->first_token);
			continue ;
		}
		prev = node;
		node = node->next;
	}
	ft_check_to_join(mini);
	ft_redir_reset(mini);
	return (SUCCESS);
}
