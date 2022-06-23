/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_workflow_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:15:46 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/23 11:52:50 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_workflow_check(t_ms *mini)
{
	t_token	*token;
	t_token	*prev;

	token = mini->first_token;
	prev = NULL;
	while (token)
	{
		if ((token->meta >= MTA_REDIR_FILE && token->meta <= MTA_REDIR)
			&& (prev == NULL
				|| (prev->meta >= MTA_REDIR_FILE && prev->meta <= MTA_REDIR
					&& token->meta == prev->meta)))
		{
			ft_syntax_error(mini, token->token[0]);
			//ft_error_comands(ERR_GEN,
			//		MSG_SYNTAX_UNX, token->token, mini);
			ft_clear_nodes(mini);
			//mini->exitstatus = 258;
			return ;
		}
		prev = token;
		token = token->next;
	}
}
