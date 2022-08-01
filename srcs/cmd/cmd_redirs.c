/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:59:49 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/29 11:06:29 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_get_data(int in_fd, int out_fd)
{
	char	*line;

	line = get_next_line(in_fd);
	while (line)
	{
		ft_putstr_fd(line, out_fd);
		free (line);
		line = get_next_line(in_fd);
	}
}

int	ft_inp_from_file(t_ms *mini)
{
	int		fd_file;

	fd_file = open(mini->first_token->args->token, O_RDONLY, S_IRWXU);
	if (fd_file < 0)
		return (ft_redir_error(errno, mini->first_token->args->token, mini));
	if (mini->first_token->out == TKN_PIPEOUT)
		ft_get_data(fd_file, STDOUT_FILENO);
	close(fd_file);
	return (SUCCESS);
}

int	ft_dup_file(t_ms *mini)
{
	int		fd_file;
	int		fd;

	if (mini->first_token->type == RDR_TO_FILE)
		fd_file = open(mini->first_token->args->token,
				O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		fd_file = open(mini->first_token->args->token,
				O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (fd_file < 0)
		return (ft_error_handler(errno, mini));
	if (mini->first_token->out == TKN_STDOUT
		|| (mini->first_token->next
			&& mini->first_token->next->meta != MTA_REDIR_FILE))
		fd = fd_file;
	else
	{
		fd = STDOUT_FILENO;
		close (fd_file);
	}
	if (mini->first_token->in != TKN_STDIN)
		ft_get_data(STDIN_FILENO, fd);
	close (fd);
	return (SUCCESS);
}
