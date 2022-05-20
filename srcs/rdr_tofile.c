/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_tofile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 22:53:53 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/15 22:53:57 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_dup_file(char *argv[])
{
	int fd_file;
	char *line;

	if (ft_strlen(argv[0]) == 1 && ft_strncmp(argv[0], ">", 1) == 0)
		fd_file = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (ft_strlen(argv[0]) == 2 && ft_strncmp(argv[0], ">>", 2) == 0)
		fd_file = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
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
	//else
	//	mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
}
