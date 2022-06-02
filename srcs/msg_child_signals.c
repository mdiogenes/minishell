/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_child_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:31:02 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/26 11:31:05 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_signals_msg(int signum)
{
	static char		*msg[] = {"", "", "", "", "", "", "",
		"", "", "", "", "Segmentation fault", "", "", "", "", ""};
	printf("[ms-42 %s : %d]\n", msg[signum], signum);
}