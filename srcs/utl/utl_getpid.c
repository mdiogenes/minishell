/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_getpid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:53:10 by msoler-e          #+#    #+#             */
/*   Updated: 2022/06/23 12:04:05 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_getpid(t_ms *mini)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_error_handler(0, mini);
		ft_free_exit(mini);
		exit (1);
	}
	if (!pid)
	{
		ft_free_exit(mini);
		exit (1);
	}
	waitpid(pid, NULL, 0);
	mini->pid = pid - 1;
	return (SUCCESS);
}
