/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:31:17 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/10 09:20:23 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_comands(char *cmd, char *msg)
{
	ft_putstr_fd("ms-42 ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(" : ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (ERROR);
}

int	ft_error_handler(int error)
{
	printf("ms-42 Error: %s\n", strerror(error));
	return (ERROR);
}

int	ft_error_free(int error, t_ms *mini)
{
	printf("ms-42 Error: %s\n", strerror(error));
	ft_free_exit(mini);
	exit (0);
	return (ERROR);
}
