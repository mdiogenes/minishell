/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_comands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:04:14 by msoler-e          #+#    #+#             */
/*   Updated: 2022/06/29 10:13:54 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_end_comand(char *cmd, char *msg)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(" : ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

long long int	ft_error_empty_exec(t_ms *mini, char *cmd)
{
	ft_putstr_fd("ms-42 : ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (mini->first_token->status == FROM_NO_PATH)
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	else
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	mini->exitstatus = 127;
	ft_process_branch(mini);
	return (127);
}

int	ft_error_comands(int error, char *cmd, char *msg, t_ms *mini)
{
	size_t	size;

	if (error == ERR_CMD)
		return (ft_error_empty_exec(mini, cmd));
	size = ft_strlen(msg);
	ft_putstr_fd("ms-42: ", STDERR_FILENO);
	if (error == ERR_CD)
	{
		ft_putstr_fd(" cd: ", STDERR_FILENO);
		mini->exitstatus = 1;
	}
	if (error == ERR_PIPE)
		mini->exitstatus = 2;
	if (error == ERR_GEN)
		mini->exitstatus = 258;
	if (error == ERR_EXIT)
	{
		if (ft_strncmp(msg, MSG_MANY_ARG, size))
			mini->exitstatus = 255;
		if (ft_strncmp(msg, MSG_NUM_ARG, size))
			mini->exitstatus = 1;
	}
	ft_putstr_end_comand(cmd, msg);
	ft_process_branch (mini);
	return (mini->exitstatus);
}
