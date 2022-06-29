/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_child_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:31:02 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/29 11:13:45 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_signals_msg(int signum)
{
	static char		*msg[] = {"", "", "", "", "", "", "",
		"", "", "", "", "Segmentation fault", "", "", "", "", ""};
	char			*sign;

	sign = ft_itoa(signum);
	ft_putstr_fd("[ms-42 ", STDERR_FILENO);
	ft_putstr_fd(msg[signum], STDERR_FILENO);
	ft_putstr_fd(" : ", STDERR_FILENO);
	ft_putstr_fd(sign, STDERR_FILENO);
	ft_putstr_fd("]\n", STDERR_FILENO);
	if (sign)
		free(sign);
}
