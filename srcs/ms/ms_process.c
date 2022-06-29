/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 23:09:37 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/29 11:24:01 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token_dir(t_ms *mini)
{
	if (mini->first_token->status == FROM_NO_PATH)
		ft_error_comands(ERR_CMD, mini->first_token->token, MSG_ERR_CMD, mini);
	else if (mini->first_token->out != TKN_STDOUT
		|| mini->first_token->type == IMP_FROM_FILE
		|| mini->first_token->type == IMP_HEREDOC)
		ft_pipes(mini);
	else if (mini->first_token->meta <= MTA_BUILDIN)
		ft_build_in(mini);
	else if (mini->first_token->meta >= MTA_BUILDIN
		&& mini->first_token->meta <= MTA_REDIR_FILE)
		ft_out_bin(mini);
	else if (mini->first_token->meta == MTA_OPERATOR)
		ft_operator(mini);
	else if (mini->first_token->meta == MTA_KEYS)
		ft_keys_process(mini);
	else if (mini->first_token->meta == MTA_NEXT)
		ft_process_branch(mini);
}

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
	else if (mini->first_token->type >= RDR_TO_FILE
		&& mini->first_token->type <= RDR_APP_FILE)
		mini->exitstatus = ft_dup_file(mini);
	//else if (mini->first_token->type == IMP_FROM_FILE)
	//	mini->exitstatus = ft_inp_from_file(mini);
	else
	{
		ft_error_comands(ERR_CMD, mini->first_token->token, MSG_ERR_CMD, mini);
		ft_process_branch(mini);
	}
	return (mini->exitstatus);
}

int	ft_out_bin(t_ms *mini)
{
	if (mini->first_token->out != TKN_STDOUT
		|| mini->first_token->type == IMP_FROM_FILE
		|| mini->first_token->type == IMP_HEREDOC)
		ft_pipes(mini);
	else
		ft_fork_and_run(mini, -1, ft_process_branch, ft_child_monitor);
	return (SUCCESS);
}
