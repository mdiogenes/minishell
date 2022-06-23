/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:17:56 by msoler-e          #+#    #+#             */
/*   Updated: 2022/06/17 15:38:25 by msoler-e         ###   ########.fr       */
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
			printf("%s", node->token);
			printf("=\"%s\"", node->args->token);
			printf("\n");
		}
		node = node->next;
	}
	ft_process_branch(mini);
	return (SUCCESS);
}
