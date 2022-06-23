/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 23:09:37 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/23 11:53:49 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_build_in(t_ms *mini)
{
	ft_prepare_node(mini, mini->first_token);
	if (mini->first_token->type == CMD_PWD)
		mini->exitstatus = ft_pwd(mini);
	else if (mini->first_token->type == CMD_CD)
		mini->exitstatus = ft_cd(mini);
	else if (mini->first_token->type == CMD_EXIT)
		mini->exitstatus = ft_exit(mini);
	else if (mini->first_token->type == CMD_ECHO)
		mini->exitstatus = ft_echo(mini);
	else if (mini->first_token->type == CMD_ENV)
		mini->exitstatus = ft_env(mini);
	else if (mini->first_token->type == CMD_UNSET)
		mini->exitstatus = ft_unset(mini);
	else if (mini->first_token->type == CMD_EXPORT)
		mini->exitstatus = ft_export_cmd(mini);
	else
	{
	//ft_error_comands(ERR_CMD, mini->first_token->token, MSG_ERR_CMD, mini);
		ft_process_branch(mini);
	}
	return (SUCCESS);
}

int	ft_out_bin(t_ms *mini)
{
	if (mini->first_token->out != TKN_STDIN
		|| mini->first_token->type == IMP_FROM_FILE
		|| mini->first_token->type == IMP_HEREDOC)
		ft_pipes(mini);
	else
		ft_fork_and_run(mini, -1, ft_process_branch);
	return (SUCCESS);
}
