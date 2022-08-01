/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_logics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 21:38:59 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/16 21:39:03 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_operator(t_ms *mini)
{
	if (mini->first_token->type == OPR_OR && mini->exitstatus > 0)
	{
		ft_process_branch(mini);
		ft_do_workflow(mini);
		return (SUCCESS);
	}
	if (mini->first_token->type == OPR_AND && mini->exitstatus == 0)
	{
		ft_process_branch(mini);
		ft_do_workflow(mini);
		return (SUCCESS);
	}
	ft_process_branch(mini);
	while (mini->first_token && mini->first_token->meta < MTA_NEXT)
		ft_process_branch(mini);
	return (ERROR);
}
