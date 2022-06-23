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

static void	ft_get_data(int in_fd, int out_fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(in_fd);
		if (!line)
			break ;
		ft_putstr_fd(line, out_fd);
		free (line);
	}
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
		exit (ft_error_handler(errno, mini));
	if (mini->first_token->out != TKN_STDIN)
		fd = STDOUT_FILENO;
	else
		fd = fd_file;
	ft_get_data(STDIN_FILENO, fd);
	if (fd != fd_file)
		close (fd_file);
	close (fd);
	exit (SUCCESS);
}

int	ft_inp_from_file(t_ms *mini)
{
	int		fd_file;

	if (mini->first_token->type == IMP_FROM_FILE)
		fd_file = open(mini->first_token->args->token, O_RDONLY, S_IRWXU);
	else
		fd_file = open(mini->first_token->args->token, O_RDONLY, S_IRWXU);
	if (fd_file < 0)
		exit (ft_error_handler(errno, mini));
	ft_get_data(fd_file, STDOUT_FILENO);
	close(fd_file);
	exit (SUCCESS);
}

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
			break ;
		ft_putstr_fd(line, STDOUT_FILENO);
		free (line);
	}
	if (line)
		free (line);
	exit (SUCCESS);
}
