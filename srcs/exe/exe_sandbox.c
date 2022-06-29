/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_sandbox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:08:57 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/28 14:29:45 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_sandbox(t_ms *mini, int (f)(t_ms *), int n)
{
	f(mini);
	if (n)
		n++;
	exit(mini->exitstatus);
}
