/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:26:59 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/09 20:27:02 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_ls_print(DIR *dir, t_ms *mini)
{
	struct dirent	*files;
	int				list;
	size_t			rst;

	list = 0;
	errno = 0;
	rst = 0;
	while (1)
	{
		files = readdir(dir);
		if (!files)
			break ;
		if (list == 5 && printf("\n"))
			list = 0;
		if (ft_strncmp(files->d_name, ".", 1) != 0)
		{
			rst += printf("%-20s", files->d_name);
			list++;
		}
	}
	if (errno != 0)
		return (ft_error_handler(errno, mini));
	return (rst);
}

int	ft_ls(t_ms *mini)
{
	DIR				*dir;

	if (mini->first_token->args)
		dir = opendir(mini->first_token->args->token);
	else
		dir = opendir(mini->path);
	if (!dir)
	{
		ft_process_branch(mini);
		return (ft_error_handler(errno, mini));
	}
	if (ft_ls_print(dir, mini) != 0)
		printf("\n");
	ft_process_branch(mini);
	ft_export_var("?", "0", SYS_HIDDEN, mini);
	closedir(dir);
	return (SUCCESS);
}