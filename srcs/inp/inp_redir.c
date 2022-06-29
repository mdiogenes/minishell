/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 20:52:04 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/26 20:52:06 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fix_cmd(t_token *node, t_token **cmd)
{
	t_token	*command;

	command = *cmd;
	if (command)
		node->in = TKN_PIPEIN;
	if (command && node->next && node->next->type >= RDR_TO_FILE
		&& node->next->type <= RDR_APP_FILE)
		node->out = TKN_PIPEOUT;
	if (ft_size_branch(node->args) > 1)
	{
		if (command == NULL)
		{
			command = node->args->next;
			command->type = ft_read_from_node(command->token);
			command->meta = ft_get_meta_type(command->type);
			command->args = command->next;
			command->next = node->next;
			node->next = command;
			command->out = TKN_PIPEOUT;
			*cmd = command;
		}
		else
			ft_inp_append(&command->args, node->args->next);
		node->args->next = NULL;
	}
}

int	ft_inp_redir(t_ms *mini)
{
	t_token	*node;
	t_token	*cmd;

	node = mini->first_token;
	cmd = NULL;
	while (node)
	{
		if (node->type >= IMP_FROM_FILE && node->type <= IMP_HEREDOC)
		{
			if (node->next)
				node->next->in = TKN_PIPEIN;
		}
		if (node->type >= RDR_TO_FILE && node->type <= RDR_APP_FILE)
			ft_fix_cmd(node, &cmd);
		if (node->meta >= MTA_BUILDIN && node->meta <= MTA_OUTEXE)
			cmd = node;
		if (node->meta >= MTA_REDIR)
			cmd = NULL;
		node = node->next;
	}
	return (SUCCESS);
}
