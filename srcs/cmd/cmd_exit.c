/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:28:40 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/11 13:28:44 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_ms *mini)
{
	size_t	size;

	size = ft_count_node(mini);
	if (size != 1)
		return (ft_error_comands(mini->first_token->token, MSG_MANY_ARG));
	ft_free_exit(mini);
	exit (0);
}
