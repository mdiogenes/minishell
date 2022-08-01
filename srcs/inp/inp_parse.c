/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 00:05:50 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/07 10:52:59 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	ft_clear_workflow(t_ms *mini)
{
	t_token	*next;

	while (mini->first_token
		&& mini->first_token->meta < MTA_NEXT)
	{
		next = mini->first_token->next;
		ft_delete_node(mini->first_token);
		mini->first_token = next;
	}
}

int	ft_do_workflow(t_ms *mini)
{
	if (mini->first_token == NULL)
		return (ERROR);
	if (ft_workflow(mini) == ERROR)
	{
		ft_clear_workflow(mini);
		return (ft_do_workflow(mini));
	}
	return (SUCCESS);
}

int	ft_parse(t_ms *mini)
{
	if (ft_load_input(mini) == ERROR)
		return (ERROR);
	if (mini->first_token == NULL)
		return (ERROR);
	add_history(mini->line);
	if (ft_do_workflow(mini) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
