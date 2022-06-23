/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 00:05:50 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/23 11:47:50 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse(t_ms *mini)
{
	mini->line = ft_strtrim_clean(mini->line, " \n\t");
	if (ft_load_input(mini) == ERROR)
		return (ERROR);
	if (mini->first_token == NULL)
		return (ERROR);
	ft_print_tree_debug("Parse. primera carga", mini->first_token);
	if (ft_workflow(mini) == ERROR)
		return (ERROR);
	ft_print_tree_debug("Parse. despues ft_workflow", mini->first_token);
	return (SUCCESS);
}

void	ft_clean_quotes(t_ms *mini)
{
	t_token	*node;
	t_token	*prev;

	node = mini->first_token;
	prev = NULL;
	while (node)
	{
		if (node->type == CMD_LITERAL || node->type == CMD_EXPAND)
		{
			if (ft_count_char(node->token, '"') > 0
				|| ft_count_char(node->token, '\'') > 0)
			{
				node->token = ft_strtrim_clean(node->token, "\"\'");
				if (ft_strlen(node->token) == 0)
					node->meta = MTA_NULL_TOKEN;
			}
		}
		prev = node;
		node = node->next;
	}
}

void	ft_prepare_node(t_ms *mini, t_token *token)
{
	DIR	*dir;

	if (!token || !token->args)
		return ;
	dir = opendir(mini->path);
	if (!dir)
	{
		printf("gestionar este error?");
		return ;
	}
	if (token->args)
		ft_get_expand(mini, token->args);
	if (token->type == CMD_ECHO && token->args)
	{
		if (ft_strict_cmp(token->args->token, "*") != 0)
			ft_solve_wildcards(mini, token, token->args, dir);
	}
	else
		ft_solve_wildcards(mini, token, token->args, dir);
	ft_print_tree_debug("Despues de expand y wildcard", mini->first_token);
	closedir(dir);
}
