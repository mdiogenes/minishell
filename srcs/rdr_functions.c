/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 22:53:53 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/01 11:44:35 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dup_file(t_ms *mini)
{
	int		fd_file;
	char	*line;

	if (mini->first_token->type == RDR_TO_FILE)
		fd_file = open(mini->first_token->args->token,
				O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		fd_file = open(mini->first_token->args->token,
				O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (fd_file < 0)
		return (ft_error_handler(errno, mini));
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		ft_putstr_fd(line, fd_file);
		free (line);
	}
	close(fd_file);
	exit (SUCCESS);
}

int	ft_inp_from_file(t_ms *mini)
{
	int		fd_file;
	char	*line;

	if (mini->first_token->type == IMP_FROM_FILE)
		fd_file = open(mini->first_token->args->token, O_RDONLY, S_IRWXU);
	else
		fd_file = open(mini->first_token->args->token, O_RDONLY, S_IRWXU);
	if (fd_file < 0)
		return (ft_error_handler(errno, mini));
	while (1)
	{
		line = get_next_line(fd_file);
		if (!line)
			break ;
		ft_putstr_fd(line, STDOUT_FILENO);
		free (line);
	}
	close(fd_file);
	exit (SUCCESS);
}
