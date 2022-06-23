/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_preprocess.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 00:27:59 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/18 00:28:02 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	*ft_is_bin_exe(char *token, t_ms *mini)
{
	char		*to_test;
	struct stat	data;
	size_t		i;
	int			eval;

	i = 0;
	while (mini->bin_paths[i])
	{
		to_test = ft_strjoin_char(mini->bin_paths[i], token, '/');
		eval = stat(to_test, &data);
		if (eval == 0 && data.st_mode == 33261)
			return (to_test);
		free(to_test);
		i++;
	}
	return (NULL);
}

static inline int	ft_update_node(t_token *token, char *cmd)
{
	token->type = CMD_EXE;
	token->meta = MTA_OUTEXE;
	if (cmd == NULL)
		return (IS_CMD);
	free (token->token);
	token->token = cmd;
	return (IS_CMD);
}

static inline int	ft_update_arg(t_token *token)
{
	token->type = NO_TYPE;
	token->meta = MTA_ARGS;
	return (IS_CMD);
}

int	ft_input_preprocess(t_ms *mini)
{
	t_token	*token;
	int		cmd;

	if (ft_open_nodes(mini) != SUCCESS)
		return (ERROR);
	token = mini->first_token;
	cmd = NO_CMD;
	while (token)
	{
		if (cmd == NO_CMD && token->meta >= MTA_BUILDIN
			&& token->meta <= MTA_OUTEXE)
			cmd = IS_CMD;
		else if (cmd == NO_CMD && token->type <= CMD_LITERAL)
			cmd = ft_update_node(token, ft_is_bin_exe(token->token, mini));
		else if (cmd == IS_CMD && token->meta >= MTA_BUILDIN
			&& token->meta <= MTA_OUTEXE)
			cmd = ft_update_arg(token);
		else if (token->meta == MTA_REDIR_FILE)
			cmd = IS_CMD;
		if (token->meta >= MTA_REDIR && token->meta <= MTA_KEYS)
			cmd = NO_CMD;
		token = token->next;
	}
	return (SUCCESS);
}
