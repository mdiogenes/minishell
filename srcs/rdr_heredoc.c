/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:11:12 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/23 11:26:16 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(t_ms *mini)
{
	char	*line;
	char	*lim;
	size_t	len_lim;

	lim = mini->first_token->args->token;
	len_lim = ft_strlen(lim);
	while (1)
	{
		write(STDIN_FILENO, "\e[32mms-42_heredoc>\e[0m ", 24);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strlen(line) == (len_lim + 1)
			&& ft_strncmp(line, lim, len_lim) == 0)
		{
			free (line);
			break ;
		}
		ft_putstr_fd(line, STDOUT_FILENO);
		free (line);
	}
	exit (SUCCESS);
}
