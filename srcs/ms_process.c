/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 23:09:37 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/01 10:16:16 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_build_in(t_ms *mini)
{
	if (mini->first_token->type == CMD_PWD)
		ft_putendl_fd(mini->path, STDOUT_FILENO);
	else if (mini->first_token->type == CMD_CD)
		ft_cd(mini);
	else if (mini->first_token->type == CMD_LS)
		ft_ls(mini);
	else if (mini->first_token->type == CMD_EXIT)
		ft_exit(mini);
	else if (mini->first_token->type == CMD_ECHO)
		ft_echo(mini);
	else if (mini->first_token->type == CMD_ENV)
		ft_env(mini);
	else if (mini->first_token->type == CMD_EXPORT && !mini->first_token->args)
		ft_print_vars(mini);
	else if (mini->first_token->type == CMD_EXPORT && mini->first_token->args)
	{
		ft_export_cmd(mini);
		ft_process_branch(mini);
	}
	else
	{
		ft_error_comands(mini->first_token->token, MSG_ERR_CMD);
		ft_export_var("?", "127", SYS_HIDDEN, mini);
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
		ft_fork_and_run(mini);
	return (SUCCESS);
}
