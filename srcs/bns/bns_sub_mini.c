/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_sub_mini.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 21:16:54 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/29 10:38:40 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sub_mini(t_ms *mini)
{
	int		keys_count;

	keys_count = 1;
	ft_process_branch(mini);
	ft_do_workflow(mini);
	while (mini->first_token)
	{
		if (mini->first_token->type == OPR_OPEN_K)
			keys_count++;
		if (mini->first_token->type == OPR_CLOSE_K)
		{
			keys_count--;
			if (keys_count == 0)
				break ;
		}
		ft_token_dir(mini);
	}
	if (mini->first_token->type == OPR_CLOSE_K)
		ft_process_branch(mini);
	exit(mini->exitstatus);
}

int	ft_keys_process(t_ms *mini)
{
	if (mini->first_token && mini->first_token->type == OPR_OPEN_K)
		ft_fork_and_run(mini, -1, NULL, ft_child_monitor);
	while (mini->first_token && mini->first_token->type != OPR_CLOSE_K)
		ft_process_branch(mini);
	if (mini->first_token->type == OPR_CLOSE_K)
	{
		ft_process_branch(mini);
		ft_do_workflow(mini);
	}
	return (SUCCESS);
}
