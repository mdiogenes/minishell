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

int	ft_error_handler(int error)
{
	printf("ms-42 Error: %s\n", strerror(error));
	return (0);
}

int	ft_error_free(int error, t_ms *mini)
{
	printf("ms-42 Error: %s\n", strerror(error));
	ft_free_exit(mini);
	exit (0);
	return (0);
}
