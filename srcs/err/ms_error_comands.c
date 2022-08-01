/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_comands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:04:14 by msoler-e          #+#    #+#             */
/*   Updated: 2022/07/05 16:33:03 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	ft_putstr_end_comand(char *cmd, char *msg)
{
	ft_putstr_fd(cmd, MS_STDERR);
	ft_putstr_fd(" : ", MS_STDERR);
	ft_putstr_fd(msg, MS_STDERR);
	ft_putstr_fd("\n", MS_STDERR);
}

void	ft_fix_err(char *cmd)
{
	struct stat	data;

	if (ft_strict_cmp(cmd, "..") != 0
		&& (ft_strncmp(cmd, ".", 1) == 0
			|| ft_strncmp(cmd, "/", 1) == 0))
	{
		if (stat(cmd, &data) < 0)
		{
			ft_putendl_fd(strerror(errno), MS_STDERR);
			g_mini->exitstatus = 127;
			return ;
		}
		if (S_ISDIR(data.st_mode))
		{
			ft_putstr_fd(": is a directory\n", MS_STDERR);
			g_mini->exitstatus = 126;
		}
	}
	else
		ft_putstr_fd(": command not found\n", MS_STDERR);
}

static inline int	ft_error_empty_exec(char *cmd)
{
	ft_putstr_fd("ms-42 : ", MS_STDERR);
	ft_putstr_fd(cmd, MS_STDERR);
	ft_putstr_fd(" ", MS_STDERR);
	g_mini->exitstatus = 127;
	if (g_mini->first_token->status == FROM_NO_PATH)
		ft_putstr_fd(": No such file or directory\n", MS_STDERR);
	else
	{
		if (ft_strict_cmp(cmd, ".") == 0)
		{
			g_mini->exitstatus = 2;
			ft_putstr_fd(": filename argument required\n", MS_STDERR);
		}
		else
			ft_fix_err(cmd);
	}
	ft_process_branch(g_mini);
	return (g_mini->exitstatus);
}

int	ft_error_comands(int error, char *cmd, char *msg, int (f)(t_ms *))
{
	size_t	size;

	if (error == ERR_CMD)
		return (ft_error_empty_exec(cmd));
	size = ft_strlen(msg);
	ft_putstr_fd("ms-42: ", MS_STDERR);
	if (error == ERR_CD)
		g_mini->exitstatus = 1;
	if (error == ERR_PIPE || error == ERR_EOF)
		g_mini->exitstatus = 2;
	if (error == ERR_GEN)
		g_mini->exitstatus = 258;
	if (error == ERR_EXIT)
	{
		if (ft_strncmp(msg, MSG_MANY_ARG, size))
			g_mini->exitstatus = 255;
		if (ft_strncmp(msg, MSG_NUM_ARG, size))
			g_mini->exitstatus = 1;
	}
	ft_putstr_end_comand(cmd, msg);
	if (f)
		f(g_mini);
	return (g_mini->exitstatus);
}
