/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_input_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:15:46 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/01 13:50:14 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ask_command(t_ms *mini)
{
	if (mini->line)
		free (mini->line);
	mini->line = readline("\e[32m>\e[0m ");
	if (!mini->line)
		signal_ctrld(mini);
	return (ft_load_input(mini));
}

void	ft_input_preprocess(t_ms *mini)
{
	t_token	*token;

	token = mini->first_token;
	while (token)
	{
		if (token->type == RDR_PIPE && token->next == NULL)
		{
			ft_ask_command(mini);
			continue ;
		}
		token = token->next;
	}
}

void	ft_workflow_check(t_ms *mini)
{
	t_token	*token;
	t_token	*prev;
	int		rst;

	token = mini->first_token;
	prev = NULL;
	rst = 1;
	while (token)
	{
		if (token->type >= RDR_TO_FILE && token->args == NULL)
			rst *= ft_error_comands(MSG_SYNTAX, TKN_NL);
		if (token->type == RDR_PIPE && prev == NULL)
			rst *= ft_error_comands(MSG_SYNTAX, TKN_PIPE);
		if (rst == 0)
			break ;
		prev = token;
		token = token->next;
	}
	if (rst == 0)
		ft_clear_nodes(mini);
}
