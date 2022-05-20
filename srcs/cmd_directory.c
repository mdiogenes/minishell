//* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_directory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:09:14 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/10 22:09:19 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_read_from_node(char *token)
{
	static char		*command[] = {"'", "\"", "$", "pwd", "cd", "ls", "echo",
		"export", "unset", "env", "exit", "./", "|", ">", ">>"};
	static size_t	sizes[TOKEN_ENUM] = {1, 1, 1, 3, 2, 2, 4, 6, 5, 3, 4, 2, 1, 1, 2};
	int				i;
	size_t			len;

	i = 0;
	while (command[i])
	{
		len = ft_strlen(token);
		if (len == sizes[i] && ft_strncmp(token, command[i], sizes[i]) == 0)
			return (i + 1);
		if (len > 2 && (i + 1) == CMD_EXE
			&& ft_strncmp(token, command[i], sizes[i]) == 0)
			return (i + 1);
		if (token[0] == 39 && token[len - 1] == 39)
			return (CMD_LITERAL);
		if (token[0] == 34 && token[len - 1] == 34)
			return (CMD_EXPAND);
		if (token[0] == '$')
			return (CMD_ENV_VAR);
		i++;
	}
	return (0);
}

int	ft_get_meta_type(int type)
{
	if (type <= CMD_ENV_VAR)
		return (MTA_ARGS);
	if (type > CMD_ENV_VAR && type <= CMD_EXIT)
		return (MTA_BUILDIN);
	if (type > CMD_EXIT && type <= CMD_EXE)
		return (MTA_OUTEXE);
	if (type > CMD_EXE)
		return (MTA_REDIR);
	return (MTA_NOTYPE);
}
