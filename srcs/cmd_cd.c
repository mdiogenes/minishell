/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:25:12 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/11 12:47:01 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_ms *mini)
{
	int		move_dir;
	char	*input;

	input = ft_substr(mini->line, 3, ft_strlen(mini->line));
	move_dir = chdir(input);
	free (input);
	if (move_dir != 0)
		return (ft_error_handler(errno));
	ft_get_path_prompt(mini);
	return (SUCCESS);
}
