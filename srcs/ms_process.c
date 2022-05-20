/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 23:09:37 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/16 23:09:41 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_build_in(t_ms *mini)
{
	if (mini->first_token->type == CMD_PWD)
		ft_putendl_fd(mini->path, STDOUT_FILENO);
	if (mini->first_token->type == CMD_CD)
		ft_cd(mini);
	if (mini->first_token->type == CMD_LS)
		ft_ls(mini);
	if (mini->first_token->type == CMD_EXIT)
		ft_exit(mini);
	if (mini->first_token->type == CMD_ECHO)
		ft_echo(mini);
	ft_process_branch(mini);
	return (SUCCESS);
}

int	ft_out_bin(t_ms *mini)
{
	if (mini->first_token->out != TKN_STDIN)
		ft_pipes(mini);
	else
		ft_fork_and_run(mini);
	return (SUCCESS);
}