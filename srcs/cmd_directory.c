/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_directory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:09:14 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/11 12:46:43 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_read_from_node(char *token)
{
	static char		*command[] = {"pwd", "cd", "ls", "echo", "export",
		"unset", "env", "exit"};
	static size_t	sizes[8] = {3, 2, 2, 4, 6, 5, 3, 4};
	int				i;
	size_t			len;

	i = 0;
	while (command[i])
	{
		len = ft_strlen(token);
		if (len == sizes[i] && ft_strncmp(token, command[i], sizes[i]) == 0)
			return (i + 1);
		i++;
	}
	return (0);
}
