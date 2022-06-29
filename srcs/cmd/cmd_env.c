/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:17:56 by msoler-e          #+#    #+#             */
/*   Updated: 2022/06/29 10:23:54 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_ms *mini)
{
	t_token	*node;

	node = mini->env;
	while (node)
	{
		if (node->type == SYS_HIDDEN)
		{
			node = node->next;
			continue ;
		}
		if (node->args)
		{
			ft_putstr_fd(node->token, STDERR_FILENO);
			ft_putstr_fd("=\"", STDERR_FILENO);
			ft_putstr_fd(node->args->token, STDERR_FILENO);
			ft_putstr_fd("\"=\"", STDERR_FILENO);
			ft_putstr_fd(node->args->token, STDERR_FILENO);
			ft_putstr_fd("\"\n", STDERR_FILENO);
		}
		node = node->next;
	}
	ft_process_branch(mini);
	return (SUCCESS);
}
